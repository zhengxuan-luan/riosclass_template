
 extern void csr_monitor(/* INPUT */int address, /* INPUT */unsigned char csr_write_valid, /* INPUT */long long write_data);

 extern void preg_sync(/* INPUT */unsigned char alu_valid, /* INPUT */unsigned char lsu_valid, /* INPUT */long long alu_data_in, /* INPUT */long long lsu_data_in, /* INPUT */int alu_address, /* INPUT */int lsu_address);

 extern void log_print(/* INPUT */unsigned char co_commit, /* INPUT */int co_pc_in, /* INPUT */unsigned char co_store_in, /* INPUT */unsigned char co_fence, /* INPUT */unsigned char co_mret, /* INPUT */unsigned char co_wfi, /* INPUT */unsigned char co_uses_csr, /* INPUT */int co_rob_rd, /* INPUT */unsigned char co_csr_iss_ctrl, /* INPUT */int co_prf_name, 
/* INPUT */int co_csr_address);
