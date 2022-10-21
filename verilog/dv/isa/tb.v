`timescale 1ns/1ps

module tb;
reg clk;
reg rst;

forever #10 clk = ~clk;


wire 
initial begin
    clk = 0;
    rst = 1;
    repeat (600) @(posedge clk);
    rst = 0;
end

hehe hehe_u(

);





endmodule