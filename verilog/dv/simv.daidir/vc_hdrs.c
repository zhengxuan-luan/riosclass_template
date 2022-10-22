#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <dlfcn.h>
#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* VCS error reporting routine */
extern void vcsMsgReport1(const char *, const char *, int, void *, void*, const char *);

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

#ifndef __VCS_IMPORT_DPI_STUB_csr_monitor
#define __VCS_IMPORT_DPI_STUB_csr_monitor
__attribute__((weak)) void csr_monitor(/* INPUT */int A_1, /* INPUT */unsigned char A_2, /* INPUT */long long A_3)
{
    static int _vcs_dpi_stub_initialized_ = 0;
    static void (*_vcs_dpi_fp_)(/* INPUT */int A_1, /* INPUT */unsigned char A_2, /* INPUT */long long A_3) = NULL;
    if (!_vcs_dpi_stub_initialized_) {
        _vcs_dpi_fp_ = (void (*)(int A_1, unsigned char A_2, long long A_3)) dlsym(RTLD_NEXT, "csr_monitor");
        _vcs_dpi_stub_initialized_ = 1;
    }
    if (_vcs_dpi_fp_) {
        _vcs_dpi_fp_(A_1, A_2, A_3);
    } else {
        const char *fileName;
        int lineNumber;
        svGetCallerInfo(&fileName, &lineNumber);
        vcsMsgReport1("DPI-DIFNF", fileName, lineNumber, 0, 0, "csr_monitor");
    }
}
#endif /* __VCS_IMPORT_DPI_STUB_csr_monitor */

#ifndef __VCS_IMPORT_DPI_STUB_preg_sync
#define __VCS_IMPORT_DPI_STUB_preg_sync
__attribute__((weak)) void preg_sync(/* INPUT */unsigned char A_1, /* INPUT */unsigned char A_2, /* INPUT */long long A_3, /* INPUT */long long A_4, /* INPUT */int A_5, /* INPUT */int A_6)
{
    static int _vcs_dpi_stub_initialized_ = 0;
    static void (*_vcs_dpi_fp_)(/* INPUT */unsigned char A_1, /* INPUT */unsigned char A_2, /* INPUT */long long A_3, /* INPUT */long long A_4, /* INPUT */int A_5, /* INPUT */int A_6) = NULL;
    if (!_vcs_dpi_stub_initialized_) {
        _vcs_dpi_fp_ = (void (*)(unsigned char A_1, unsigned char A_2, long long A_3, long long A_4, int A_5, int A_6)) dlsym(RTLD_NEXT, "preg_sync");
        _vcs_dpi_stub_initialized_ = 1;
    }
    if (_vcs_dpi_fp_) {
        _vcs_dpi_fp_(A_1, A_2, A_3, A_4, A_5, A_6);
    } else {
        const char *fileName;
        int lineNumber;
        svGetCallerInfo(&fileName, &lineNumber);
        vcsMsgReport1("DPI-DIFNF", fileName, lineNumber, 0, 0, "preg_sync");
    }
}
#endif /* __VCS_IMPORT_DPI_STUB_preg_sync */

#ifndef __VCS_IMPORT_DPI_STUB_log_print
#define __VCS_IMPORT_DPI_STUB_log_print
__attribute__((weak)) void log_print(/* INPUT */unsigned char A_1, /* INPUT */int A_2, /* INPUT */unsigned char A_3, /* INPUT */unsigned char A_4, /* INPUT */unsigned char A_5, /* INPUT */unsigned char A_6, /* INPUT */unsigned char A_7, /* INPUT */int A_8, /* INPUT */unsigned char A_9, /* INPUT */int A_10, 
/* INPUT */int A_11)
{
    static int _vcs_dpi_stub_initialized_ = 0;
    static void (*_vcs_dpi_fp_)(/* INPUT */unsigned char A_1, /* INPUT */int A_2, /* INPUT */unsigned char A_3, /* INPUT */unsigned char A_4, /* INPUT */unsigned char A_5, /* INPUT */unsigned char A_6, /* INPUT */unsigned char A_7, /* INPUT */int A_8, /* INPUT */unsigned char A_9, /* INPUT */int A_10, 
/* INPUT */int A_11) = NULL;
    if (!_vcs_dpi_stub_initialized_) {
        _vcs_dpi_fp_ = (void (*)(unsigned char A_1, int A_2, unsigned char A_3, unsigned char A_4, unsigned char A_5, unsigned char A_6, unsigned char A_7, int A_8, unsigned char A_9, int A_10, int A_11)) dlsym(RTLD_NEXT, "log_print");
        _vcs_dpi_stub_initialized_ = 1;
    }
    if (_vcs_dpi_fp_) {
        _vcs_dpi_fp_(A_1, A_2, A_3, A_4, A_5, A_6, A_7, A_8, A_9, A_10, A_11);
    } else {
        const char *fileName;
        int lineNumber;
        svGetCallerInfo(&fileName, &lineNumber);
        vcsMsgReport1("DPI-DIFNF", fileName, lineNumber, 0, 0, "log_print");
    }
}
#endif /* __VCS_IMPORT_DPI_STUB_log_print */


#ifdef __cplusplus
}
#endif

