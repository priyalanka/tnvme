/*
 * Copyright (c) 2011, Intel Corporation.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _TNVME_H_
#define _TNVME_H_

#include <stdio.h>
#include <string>
#include <vector>
#include "dnvme.h"
#include "testRef.h"

using namespace std;

#define APPNAME         "tnvme"
#define LEVEL           APPNAME
#define LOG_NRM(fmt, ...)       \
    fprintf(stderr, "%s: " fmt "\n", LEVEL, ## __VA_ARGS__);
#define LOG_ERR(fmt, ...)       \
    fprintf(stderr, "%s-err:%s:%d: " fmt "\n", LEVEL, __FILE__, __LINE__,   \
        ## __VA_ARGS__);
#define LOG_ERR_STR(str)        \
    fprintf(stderr, "%s-err:%s:%d: " "%s" "\n", LEVEL, __FILE__, __LINE__,  \
        str.c_str());
#define LOG_WARN(fmt, ...)      \
    fprintf(stderr, "%s-warn:%s:%d: " fmt "\n", LEVEL, __FILE__, __LINE__,  \
        ## __VA_ARGS__);

#ifdef DEBUG
#define LOG_DBG(fmt, ...)       \
    fprintf(stderr, "%s-dbg:%s:%d: " fmt "\n", LEVEL, __FILE__, __LINE__,   \
        ## __VA_ARGS__);
#else
#define LOG_DBG(fmt, ...)       ;
#endif


#define MAX_CHAR_PER_LINE_DESCRIPTION       63


typedef enum {
    SPECREV_10b,             // http://www.nvmexpress.org/ spec. rev. 1.0b
    SPECREVTYPE_FENCE        // always must be last element
} SpecRev;


/**
 * Combination/permutation not listed below should be considered illegal. The
 * last permutation listed, request spec'd test within spec'd group, causes
 * the zero, configuration, and sequence dependencies to become invoked, refer
 * to: https://github.com/nvmecompliance/tnvme/wiki/Test-Numbering
 *
 * req      group       xLevel      yLevel      zLevel    implies
 * -----------------------------------------------------------------------------
 * false     n/a         n/a         n/a         n/a      nothing has been requested
 * true   ==UINT_MAX     n/a         n/a         n/a      request all test within all all groups
 * true   !=UINT_MAX  ==UINT_MAX  ==UINT_MAX  ==UINT_MAX  request all test within spec'd group
 * true   !=UINT_MAX  !=UINT_MAX  !=UINT_MAX  !=UINT_MAX  request spec'd test within spec'd group
 */
struct TestTarget {
    bool            req;     // requested by cmd line
    TestRef         t;
};

struct RmmapIo {
    bool            req;     // requested by cmd line
    nvme_io_space   space;
    size_t          offset;
    size_t          size;
    nvme_acc_type   acc;
};

struct WmmapIo {
    bool            req;     // requested by cmd line
    nvme_io_space   space;
    size_t          offset;
    size_t          size;
    uint64_t        value;
    nvme_acc_type   acc;
};

struct NumQueues {
    bool            req;     // requested by cmd line
    uint16_t        ncqr;    // Number of IOCQ's requested
    uint16_t        nsqr;    // Number of IOSQ's requested
};

struct ErrorRegs {
    uint16_t        sts;     // PCI addr space STS regr bitmask
    uint16_t        pxds;    // PCI addr space PCICAP.PXDS reg bitmask
    uint16_t        aeruces; // PCI addr space AERCAP.AERUCES reg bitmask
    uint32_t        csts;    // Ctrl'r addr space CSTS reg bitmask
};

struct CmdLine {
    bool            summary;
    bool            ignore;
    bool            reset;
    size_t          loop;
    SpecRev         rev;
    TestTarget      detail;
    TestTarget      test;
    string          device;
    vector<TestRef> skiptest;
    RmmapIo         rmmap;
    WmmapIo         wmmap;
    NumQueues       numQueues;
    ErrorRegs       errRegs;
    string          log;
};


#endif
