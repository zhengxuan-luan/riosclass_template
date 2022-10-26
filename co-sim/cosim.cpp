#include <cstring>
#include <svdpi.h>
#include <stdint.h>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <svdpi.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

int preg [64] = {0};
FILE* cosim_log = NULL;

extern "C"{
#define coprint(...) fprintf(cosim_log, __VA_ARGS__)
// #define coprint(...) printf(__VA_ARGS__)
//insert into phsical_regfile.v to sync preg in C++
extern void preg_sync(svLogic alu_valid, svLogic lsu_valid, long long alu_data_in, long long lsu_data_in, int alu_address, int lsu_address){
    if(alu_valid & (alu_address != 0)){
        preg[alu_address] = alu_data_in;
    }
    if(lsu_valid & (lsu_address != 0)){
        preg[lsu_address] = lsu_data_in;
    }
    preg[0] = 0;
}

extern void get_log_handler(){
    cosim_log = fopen("greenrio_log.txt", "w+");
}
extern void close_log(){
    fclose(cosim_log);
}


bool csr_monitor_read = false;  //当发射了一条csr指令时，当它在写csr的过程中就将其打印下来，这个必然是下个commit的结果
bool csr_need_print = false; //只有特定的csr被修改时才需要打印
char const *csr_name;
long long csr_value;

extern void csr_monitor(int address, svLogic csr_write_valid, long long write_data){ //将信息保存下来， 在commit时使用
    if(csr_monitor_read && csr_write_valid){
        csr_need_print = true;
        switch(address){
            case 0x305:  //mtvec
                csr_value = write_data & 0xfffffffffffffffc;
                break;
            case 0x340:  //mscratch
                csr_value = write_data;
                break;
            case 0x341: //mepc    note that in hehe it's 32bit
                csr_value = write_data;
                break;
            case 0x342: //mcuse
                csr_value = 0x800000000000000f & write_data; 
                break;
        }
    }
}

//embed this function in rcu, when one instruction is commited, print it in the log file  
extern void log_print(svLogic co_commit, int co_pc_in, svLogic co_store_in, svLogic co_fence, svLogic co_mret, svLogic co_wfi,  svLogic co_uses_csr, int co_rob_rd, svLogic co_csr_iss_ctrl, int co_prf_name, int co_csr_address){
    if(co_commit){
        coprint("core 0: 0x00000000%08X     ", co_pc_in);
        if(co_uses_csr){  //Zicsr
            if(csr_need_print){
                coprint("CSR %s <- 0x%016lX\n", csr_name, csr_value);
                csr_need_print = false;
            } else{
                coprint("\n");
            }
            if(co_rob_rd && csr_monitor_read){
                coprint("x%d <- 0x%016lX\n", co_rob_rd, preg[co_prf_name]);
            }
            csr_monitor_read = false;
        }else if(co_fence){ //fence
            coprint("fence\n");
        }else if(co_mret){
            coprint("mret\n");
        }else if(co_wfi){
            coprint("wfi\n");
        }else if(co_store_in){
        }else {
            if(!co_uses_csr){
                if(co_rob_rd){
                    coprint("x%d <- 0x%016lX\n", co_rob_rd, preg[co_prf_name]);
                } else {
                    coprint("\n");
                }
            }
        }
    }
    if(co_csr_iss_ctrl){
        csr_monitor_read = false;
        switch(co_csr_address){
            case 0x305:  //mtvec
                csr_name = "mtvec";
                // printf("5 pc: 0x%08X\n", co_pc_in);
                csr_monitor_read = true;
                break;
            case 0x340:  //mscratch
                csr_name = "mscratch";
                csr_monitor_read = true;
                break;
            case 0x341: //mepc    note that in hehe it's 32bit
                csr_name = "mepc";
                csr_monitor_read = true;
                break;
            case 0x342: //mcause
                csr_name = "mcause";
                csr_monitor_read = true;
                break;
        }
    }
}

}



