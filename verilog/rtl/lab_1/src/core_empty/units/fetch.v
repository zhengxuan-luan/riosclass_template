`ifndef FETCH_V
`define FETCH_V
// `include "params.vh"
module fetch #(
    // parameter INS_BUFFER = 64,
    parameter BTB_SIZE = 4,
    parameter BTB_WIDTH = 2, //log2(up)
    parameter GSHARE_WIDTH = 4,
    parameter PHT_LEN = 16,
    parameter INS_BUFFER_DATA = 96,
    parameter INS_BUFFER_SIZE = 8, //need to set to 8
    parameter INS_BUFFER_SIZE_WIDTH = 3 //log2 (up)

) (
    //whole fetch
    input clk,
    input reset,
    input branch_valid_i, 

    //btb from fu
    input [31:0] btb_req_pc, 
    input [31:0] btb_predict_target, 

    //gshare from fu
    input [31:0] prev_pc,
    input prev_taken,

    //instruction buffer
    input rd_en,
    output [31:0] pc_out,
    output [31:0] next_pc_out,
    output [31:0] instruction_out,

    // from fu
    input [31:0] real_branch,
    
    // from exception ctrl
    input trap,
    input mret,
    input wfi,

    // from csr
    input [31:0] trap_vector,
    input [31:0] mret_vector,

    //from icache 
    input icache_req_ready,
    input icache_resp_valid,
    input [31:0] fetch_data,
    input [31:0] icache_resp_address,
    
    // to icache
    output icache_resp_ready,
    output reg icache_req_valid,
    output [31:0] fetch_address,


    //for test
    output ins_empty,

    // exceptions
    output exception_valid_o,
    output [EXCEPTION_CODE_WIDTH - 1 : 0] ecause_o
);

reg [31:0] pc;
wire branch_predict_wrong;

reg rff_icache_resp; //to match misfetch signal, make sure the next response from icache after branch should be ignore

assign fetch_address = pc;
reg [31:0] next_pc;
wire judge_from_gshare;
wire btb_taken;
// wire buffer_full;
wire [31:0] pc_from_btb;
assign branch_predict_wrong = branch_valid_i && ((real_branch != pc_out) || ins_empty);
wire flush = (branch_predict_wrong | trap | mret) & !ins_empty;

assign exception_valid_o = pc[1:0] != 2'b00;
assign ecause_o = (pc[1:0] != 2'b00) ? EXCEPTION_INSTR_ADDR_MISALIGNED : 0;

wire buffer_full;
reg [31:0] ins_pc_in;
wire [31:0] ins_next_pc_in;
wire [31:0] instruction_in;

reg rff_misfetch;
wire misfetch;
wire pc_unpredict_taken;

//next pc 
always @(*) begin
    if (wfi) begin
        next_pc = pc;
    end else if (trap) begin
        next_pc = trap_vector;
    end else if (mret) begin
        next_pc = mret_vector;
    end else if (branch_predict_wrong) begin
        next_pc = real_branch;
    end else if (btb_taken && !judge_from_gshare) begin //need && judge_from_gshare
        next_pc = pc_from_btb;
    end else begin
        next_pc = pc + 4;
    end
end

assign pc_unpredict_taken = trap | mret | branch_predict_wrong;

//pc switch
always @(posedge clk) begin
    if (reset) begin
        pc <= RESET_VECTOR;
    end else if ((icache_req_ready & icache_req_valid) | pc_unpredict_taken) begin
        pc <= next_pc;
    end
end
    
always @(posedge clk) begin
    if (wfi || buffer_full || reset) begin
        icache_req_valid <= 0;
    end else begin
        icache_req_valid <= 1;
    end
end

always @(posedge clk) begin
    if (reset) begin
        ins_pc_in <= RESET_VECTOR;
    end else if (branch_predict_wrong | trap | mret) begin 
        ins_pc_in <= next_pc;
    end else if(icache_req_ready & icache_req_valid) begin
        ins_pc_in <= pc; 
    end
end

/* verilator lint_off LATCH */
// always @(*) begin
//     if (branch_predict_wrong | trap | mret) begin
//         rff_misfetch = 1;
//     end else if (rff_icache_resp) begin
//         rff_misfetch = 0;
//     end
// end
/* verilator lint_on LATCH */

always @(posedge clk) begin
    if (reset) begin
        rff_misfetch <= 0;
    end if ((branch_predict_wrong | trap | mret) && !(icache_resp_ready & icache_resp_valid)) begin
        rff_misfetch <= 1;
    end else if (icache_resp_ready & icache_resp_valid) begin
        rff_misfetch <= 0;
    end
end

assign misfetch = rff_misfetch | branch_predict_wrong | trap | mret;

// always @(posedge clk) begin
//     if (reset) begin
//         rff_icache_resp <= 0;
//     end else if (icache_resp_ready & icache_resp_valid) begin
//         rff_icache_resp <= 1;
//     end else begin
//         rff_icache_resp <= 0;
//     end
// end


assign ins_next_pc_in = ins_pc_in + 4;
assign instruction_in = fetch_data;

assign icache_resp_ready = !wfi && !buffer_full;
wire instr_buffer_wr_en = icache_resp_ready && icache_resp_valid && (icache_resp_address == ins_pc_in) && !misfetch; // resp_address can equal both ins_next_pc_in and pc 

btb #(
    .BTB_SIZE(BTB_SIZE),
    .BTB_WIDTH(BTB_WIDTH)
) btb_u(
    .clk(clk),
    .reset(reset),
    .pc_in(pc),
    .buffer_hit(btb_taken),
    .next_pc_out(pc_from_btb),
    .is_req_pc(branch_valid_i),
    .req_pc(btb_req_pc),
    .predict_target(btb_predict_target)
);

gshare #(
    .GSHARE_WIDTH(GSHARE_WIDTH),
    .PHT_LEN(PHT_LEN)
) gshare_u(
    .clk(clk),
    .reset(reset),
    .pc(pc),
    .prev_pc(prev_pc),
    .prev_branch_in(branch_valid_i),
    .prev_taken(prev_taken),
    .cur_pred(judge_from_gshare)
);

ins_buffer #(
    .INS_BUFFER_DATA(INS_BUFFER_DATA),
    .INS_BUFFER_SIZE(INS_BUFFER_SIZE),
    .INS_BUFFER_SIZE_WIDTH(INS_BUFFER_SIZE_WIDTH)
) buffer_u(
    .clk(clk),
    .reset(reset),
    .flush(flush),
    .pc_in(ins_pc_in),
    .next_pc_in(ins_next_pc_in),
    .instruction_in(instruction_in),
    .rd_en(rd_en),
    .wr_en(instr_buffer_wr_en),
    .pc_out(pc_out),
    .next_pc_out(next_pc_out),
    .instruction_out(instruction_out),
    .ins_full(buffer_full),
    .ins_empty(ins_empty)
);

////////////////////////////////////fake icache
//need change fifo to fifo test in instruction_buffer
// fake_icache hello(
//     .clk(clk),
//     .reset(reset),
//     .fetch_address(fetch_address),
//     .instruction(fetch_data)
// );





//////////////////////////////////////////////
endmodule

`endif // FETCH_V
