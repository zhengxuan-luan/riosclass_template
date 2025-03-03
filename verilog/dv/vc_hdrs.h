#ifndef _VC_HDRS_H
#define _VC_HDRS_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <dlfcn.h>
#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _VC_TYPES_
#define _VC_TYPES_
/* common definitions shared with DirectC.h */

typedef unsigned int U;
typedef unsigned char UB;
typedef unsigned char scalar;
typedef struct { U c; U d;} vec32;

#define scalar_0 0
#define scalar_1 1
#define scalar_z 2
#define scalar_x 3

extern long long int ConvUP2LLI(U* a);
extern void ConvLLI2UP(long long int a1, U* a2);
extern long long int GetLLIresult();
extern void StoreLLIresult(const unsigned int* data);
typedef struct VeriC_Descriptor *vc_handle;

#ifndef SV_3_COMPATIBILITY
#define SV_STRING const char*
#else
#define SV_STRING char*
#endif

#endif /* _VC_TYPES_ */


 extern void csr_monitor(/* INPUT */int address, /* INPUT */unsigned char csr_write_valid, /* INPUT */long long write_data);

 extern void preg_sync(/* INPUT */unsigned char alu_valid, /* INPUT */unsigned char lsu_valid, /* INPUT */long long alu_data_in, /* INPUT */long long lsu_data_in, /* INPUT */int alu_address, /* INPUT */int lsu_address);

 extern void log_print(/* INPUT */unsigned char co_commit, /* INPUT */int co_pc_in, /* INPUT */unsigned char co_store_in, /* INPUT */unsigned char co_fence, /* INPUT */unsigned char co_mret, /* INPUT */unsigned char co_wfi, /* INPUT */unsigned char co_uses_csr, /* INPUT */int co_rob_rd, /* INPUT */unsigned char co_csr_iss_ctrl, /* INPUT */int co_prf_name, 
/* INPUT */int co_csr_address);

 extern void get_log_handler();

 extern void close_log();

#ifdef __cplusplus
}
#endif


#endif //#ifndef _VC_HDRS_H

