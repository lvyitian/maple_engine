/*
 * Copyright (C) [2020] Futurewei Technologies, Inc. All rights reverved.
 *
 * Licensed under the Mulan Permissive Software License v2.
 * You can use this software according to the terms and conditions of the MulanPSL - 2.0.
 * You may obtain a copy of MulanPSL - 2.0 at:
 *
 *   https://opensource.org/licenses/MulanPSL-2.0
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the MulanPSL - 2.0 for more details.
 */

#ifndef MAPLERE_MFUNCTION_H_
#define MAPLERE_MFUNCTION_H_

#include <vector>
#include <dlfcn.h>

#include <unistd.h>
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

#include "cmpl.h"
#include "intrinsic_op.h"  // MIRIntrinsicId

#include "mvalue.h"
#include "mexception.h"
#include "mdebug.h"

#define DEBUGSYMBOL(symaddr, msg) if(debug_engine & kEngineDebugMethod) \
    do { \
        Dl_info info; \
        long tid = gettid(); \
        if(dladdr(symaddr, &info)) \
            fprintf(stderr, "Debug [%ld] addr2line -f -e %s 0x%lx\nDebug [%ld] Symbol: 0x%016llx: %s\n", \
                tid, info.dli_fname, (char*)symaddr - (char*)info.dli_fbase, \
                tid, (unsigned long long)symaddr, msg); \
        else \
            fprintf(stderr, "Debug [%ld] Symbol: 0x%016llx: <unknown> : %s\n", \
                tid, (unsigned long long)symaddr, msg); \
    } while(0)
#define DEBUGMETHODSYMBOL(symaddr, msg, eval_size) if(debug_engine & kEngineDebugMethod) \
    do { \
        char buff[20]; \
        snprintf(buff, 20, " eval_depth=%d", eval_size); \
        Dl_info info; \
        long tid = gettid(); \
        if(dladdr(symaddr, &info)) { \
            func.lib_addr = (uint8_t*)info.dli_fbase; \
            fprintf(stderr, "Debug [%ld] addr2line -f -e %s 0x%lx\nDebug [%ld] Symbol: 0x%016llx, lib_addr: 0x%016llx, %s%s\n", \
                tid, info.dli_fname, (char*)symaddr - (char*)func.lib_addr, \
                tid, (unsigned long long)symaddr, (unsigned long long)func.lib_addr, msg, buff); \
        } else { \
            func.lib_addr = nullptr; \
            fprintf(stderr, "Debug [%ld] Symbol: 0x%016llx: <unknown> : %s%s\n", \
                tid, (unsigned long long)symaddr, msg, buff); \
        } \
    } while(0)

#define VARNAMELENGTH 16

namespace maple {

    typedef struct {
        uint32_t   header_size;
        uint16_t   formals_num; // The number of method parameters is limited to 255 for Java
        uint16_t   locals_num;
        uint16_t   eval_depth;
        uint16_t   method_flags;
        uint8_t    primtype_table[0]; // for all formals, return value, throw value and locals
    } method_header_t;

    using ffi_fp_t = void(*const)();

    // For each function with Maple IR
    class MFunction {
        public:
            typedef std::vector<MValue>   MStack;

            uint8_t                      *pc;
            const method_header_t* const  header;
            const MFunction              *caller;

            MStack::size_type             sp;            // evaluation stack pointer
            mutable MStack                operand_stack; // for locals, return value, throw value and evaluation stack

            uint8_t                      *try_catch_pc;

            uint8_t                      *lib_addr;
            char                         *var_names;     // names of all formal and local variables

            explicit MFunction(const method_header_t* const current_header,
                               const MFunction *func_caller,
                               bool is_shim = false);
            ~MFunction();

            void ResetSP();

            void direct_call(PrimType ret_ptyp, const uint32_t arg_num, uint8_t* const pc);
            void indirect_call(PrimType ret_ptyp, const uint32_t arg_num);
            void invoke_intrinsic(PrimType ret_ptyp, const uint32_t arg_num, MIRIntrinsicID intrinsic);
            void throw_exception();

            void call_with_ffi(PrimType ret_ptyp, const uint32_t actual_num, ffi_fp_t fp);
    };

    MValue maple_invoke_method(const method_header_t* const mir_header, const MFunction *caller);

}
#endif // MAPLERE_MFUNCTION_H_
