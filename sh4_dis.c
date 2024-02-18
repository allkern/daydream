#include <stdio.h>

#include "sh4_dis.h"

#define ROTL16(v, r) ((((v) << r) | ((v) >> (16 - r))) & 0xffff)
#define ROTR16(v, r) ((((v) >> r) | ((v) << (16 - r))) & 0xffff)

char* sh4_disassemble(uint16_t opcode, char* buf, sh4d_state* state) {
    char* dst = buf;

    if (state) if (state->print_address)
        dst += sprintf(dst, "%08x: ", state->pc);

    if (state) if (state->print_opcode)
        dst += sprintf(dst, "%04x ", opcode);

    uint16_t opcode_f00f = opcode & 0xf00f;

    switch (opcode & 0xf00f) {
        case 0x6003: dst += sprintf(dst, "%-7s R%u, R%u", "mov", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x6000: dst += sprintf(dst, "%-7s @R%u, R%u", "mov.b", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x6001: dst += sprintf(dst, "%-7s @R%u, R%u", "mov.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x6002: dst += sprintf(dst, "%-7s @R%u, R%u", "mov.l", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x2000: dst += sprintf(dst, "%-7s R%u, @R%u", "mov.b", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x2001: dst += sprintf(dst, "%-7s R%u, @R%u", "mov.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x2002: dst += sprintf(dst, "%-7s R%u, @R%u", "mov.l", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x6004: dst += sprintf(dst, "%-7s @R%u+, R%u", "mov.b", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x6005: dst += sprintf(dst, "%-7s @R%u+, R%u", "mov.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x6006: dst += sprintf(dst, "%-7s @R%u+, R%u", "mov.l", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x2004: dst += sprintf(dst, "%-7s R%u, @-R%u", "mov.b", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x2005: dst += sprintf(dst, "%-7s R%u, @-R%u", "mov.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x2006: dst += sprintf(dst, "%-7s R%u, @-R%u", "mov.l", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x000c: dst += sprintf(dst, "%-7s @(R0,R%u), R%u", "mov.b", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x000d: dst += sprintf(dst, "%-7s @(R0,R%u), R%u", "mov.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x000e: dst += sprintf(dst, "%-7s @(R0,R%u), R%u", "mov.l", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x0004: dst += sprintf(dst, "%-7s R%u, @(R0,R%u)", "mov.b", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x0005: dst += sprintf(dst, "%-7s R%u, @(R0,R%u)", "mov.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x0006: dst += sprintf(dst, "%-7s R%u, @(R0,R%u)", "mov.l", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x6008: dst += sprintf(dst, "%-7s R%u, R%u", "swap.b", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x6009: dst += sprintf(dst, "%-7s R%u, R%u", "swap.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x200d: dst += sprintf(dst, "%-7s R%u, R%u", "xtrct", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x300c: dst += sprintf(dst, "%-7s R%u, R%u", "add", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x300e: dst += sprintf(dst, "%-7s R%u, R%u", "addc", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x300f: dst += sprintf(dst, "%-7s R%u, R%u", "addv", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x3000: dst += sprintf(dst, "%-7s R%u, R%u", "cmp/eq", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x3002: dst += sprintf(dst, "%-7s R%u, R%u", "cmp/hs", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x3003: dst += sprintf(dst, "%-7s R%u, R%u", "cmp/ge", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x3006: dst += sprintf(dst, "%-7s R%u, R%u", "cmp/hi", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x3007: dst += sprintf(dst, "%-7s R%u, R%u", "cmp/gt", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x200c: dst += sprintf(dst, "%-7s R%u, R%u", "cmp/str", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x2007: dst += sprintf(dst, "%-7s R%u, R%u", "div0s", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x3004: dst += sprintf(dst, "%-7s R%u, R%u", "div1", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x300d: dst += sprintf(dst, "%-7s R%u, R%u", "dmuls.l", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x3005: dst += sprintf(dst, "%-7s R%u, R%u", "dmulu.l", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x600e: dst += sprintf(dst, "%-7s R%u, R%u", "exts.b", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x600f: dst += sprintf(dst, "%-7s R%u, R%u", "exts.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x600c: dst += sprintf(dst, "%-7s R%u, R%u", "extu.b", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x600d: dst += sprintf(dst, "%-7s R%u, R%u", "extu.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x000f: dst += sprintf(dst, "%-7s @R%u+, @R%u+", "mac.l", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x400f: dst += sprintf(dst, "%-7s @R%u+, @R%u+", "mac.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x0007: dst += sprintf(dst, "%-7s R%u, R%u", "mul.l", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x200f: dst += sprintf(dst, "%-7s R%u, R%u", "muls.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x200e: dst += sprintf(dst, "%-7s R%u, R%u", "mulu.w", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x600b: dst += sprintf(dst, "%-7s R%u, R%u", "neg", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x600a: dst += sprintf(dst, "%-7s R%u, R%u", "negc", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x3008: dst += sprintf(dst, "%-7s R%u, R%u", "sub", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x300a: dst += sprintf(dst, "%-7s R%u, R%u", "subc", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x300b: dst += sprintf(dst, "%-7s R%u, R%u", "subv", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x2009: dst += sprintf(dst, "%-7s R%u, R%u", "and", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x6007: dst += sprintf(dst, "%-7s R%u, R%u", "not", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x200b: dst += sprintf(dst, "%-7s R%u, R%u", "or", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x2008: dst += sprintf(dst, "%-7s R%u, R%u", "tst", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x200a: dst += sprintf(dst, "%-7s R%u, R%u", "xor", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x400c: dst += sprintf(dst, "%-7s R%u, R%u", "shad", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x400d: dst += sprintf(dst, "%-7s R%u, R%u", "shld", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf00c: dst += sprintf(dst, "%-7s FR%u, FR%u", "fmov", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf008: dst += sprintf(dst, "%-7s @R%u, FR%u", "fmov.s", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf00a: dst += sprintf(dst, "%-7s FR%u, @R%u", "fmov.s", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf009: dst += sprintf(dst, "%-7s @R%u+, FR%u", "fmov.s", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf00b: dst += sprintf(dst, "%-7s FR%u, @-R%u", "fmov.s", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf006: dst += sprintf(dst, "%-7s @(R0,R%u), FR%u", "fmov.s", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf007: dst += sprintf(dst, "%-7s FR%u, @(R0,R%u)", "fmov.s", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf000: dst += sprintf(dst, "%-7s FR%u, FR%u", "fadd", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf001: dst += sprintf(dst, "%-7s FR%u, FR%u", "fsub", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf002: dst += sprintf(dst, "%-7s FR%u, FR%u", "fmul", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf00e: dst += sprintf(dst, "%-7s FR0, FR%u, FR%u", "fmac", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf003: dst += sprintf(dst, "%-7s FR%u, FR%u", "fdiv", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf004: dst += sprintf(dst, "%-7s FR%u, FR%u", "fcmp/eq", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0xf005: dst += sprintf(dst, "%-7s FR%u, FR%u", "fcmp/gt", (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
    }

    switch (opcode & 0xf000) {
        case 0xe000: dst += sprintf(dst, "%-7s #0x%02x, R%u", "mov", (opcode & 0x00ff) >> 0, (opcode & 0x0f00) >> 8); return buf;
        case 0x9000: dst += sprintf(dst, "%-7s @(%+i,PC), R%u", "mov.w", (opcode & 0x00ff) >> 0, (opcode & 0x0f00) >> 8); return buf;
        case 0xd000: dst += sprintf(dst, "%-7s @(%+i,PC), R%u", "mov.l", (opcode & 0x00ff) >> 0, (opcode & 0x0f00) >> 8); return buf;
        case 0x5000: dst += sprintf(dst, "%-7s @(%+i,R%u), R%u", "mov.l", (opcode & 0x000f) >> 0, (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x1000: dst += sprintf(dst, "%-7s R%u, @(%+i,R%u)", "mov.l", (opcode & 0x000f) >> 0, (opcode & 0x00f0) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x7000: dst += sprintf(dst, "%-7s #0x%02x, R%u", "add", (opcode & 0x00ff) >> 0, (opcode & 0x0f00) >> 8); return buf;
        case 0xa000: dst += sprintf(dst, "%-7s %+i", "bra", (opcode & 0x0fff) >> 0); return buf;
        case 0xb000: dst += sprintf(dst, "%-7s %+i", "bsr", (opcode & 0x0fff) >> 0); return buf;
    }

    switch (opcode & 0xff00) {
        case 0xc700: dst += sprintf(dst, "%-7s @(%+i,PC), R0", "mova", (opcode & 0x00ff) >> 0); return buf;
        case 0x8400: dst += sprintf(dst, "%-7s @(%+i,R%u), R0", "mov.b", (opcode & 0x000f) >> 0, (opcode & 0x00f0) >> 4); return buf;
        case 0x8500: dst += sprintf(dst, "%-7s @(%+i,R%u), R0", "mov.w", (opcode & 0x000f) >> 0, (opcode & 0x00f0) >> 4); return buf;
        case 0x8000: dst += sprintf(dst, "%-7s R0, @(%+i,R%u)", "mov.b", (opcode & 0x000f) >> 0, (opcode & 0x00f0) >> 4); return buf;
        case 0x8100: dst += sprintf(dst, "%-7s R0, @(%+i,R%u)", "mov.w", (opcode & 0x000f) >> 0, (opcode & 0x00f0) >> 4); return buf;
        case 0xc400: dst += sprintf(dst, "%-7s @(%+i,GBR), R0", "mov.b", (opcode & 0x00ff) >> 0); return buf;
        case 0xc500: dst += sprintf(dst, "%-7s @(%+i,GBR), R0", "mov.w", (opcode & 0x00ff) >> 0); return buf;
        case 0xc600: dst += sprintf(dst, "%-7s @(%+i,GBR), R0", "mov.l", (opcode & 0x00ff) >> 0); return buf;
        case 0xc000: dst += sprintf(dst, "%-7s R0, @(%+i,GBR)", "mov.b", (opcode & 0x00ff) >> 0); return buf;
        case 0xc100: dst += sprintf(dst, "%-7s R0, @(%+i,GBR)", "mov.w", (opcode & 0x00ff) >> 0); return buf;
        case 0xc200: dst += sprintf(dst, "%-7s R0, @(%+i,GBR)", "mov.l", (opcode & 0x00ff) >> 0); return buf;
        case 0x8800: dst += sprintf(dst, "%-7s #0x%02x, R0", "cmp/eq", (opcode & 0x00ff) >> 0); return buf;
        case 0xc900: dst += sprintf(dst, "%-7s #0x%02x, R0", "and", (opcode & 0x00ff) >> 0); return buf;
        case 0xcd00: dst += sprintf(dst, "%-7s #0x%02x, @(R0,GBR)", "and.b", (opcode & 0x00ff) >> 0); return buf;
        case 0xcb00: dst += sprintf(dst, "%-7s #0x%02x, R0", "or", (opcode & 0x00ff) >> 0); return buf;
        case 0xcf00: dst += sprintf(dst, "%-7s #0x%02x, @(R0,GBR)", "or.b", (opcode & 0x00ff) >> 0); return buf;
        case 0xc800: dst += sprintf(dst, "%-7s #0x%02x, R0", "tst", (opcode & 0x00ff) >> 0); return buf;
        case 0xcc00: dst += sprintf(dst, "%-7s #0x%02x, @(R0,GBR)", "tst.b", (opcode & 0x00ff) >> 0); return buf;
        case 0xca00: dst += sprintf(dst, "%-7s #0x%02x, R0", "xor", (opcode & 0x00ff) >> 0); return buf;
        case 0xce00: dst += sprintf(dst, "%-7s #0x%02x, @(R0,GBR)", "xor.b", (opcode & 0x00ff) >> 0); return buf;
        case 0x8b00: dst += sprintf(dst, "%-7s %+i", "bf", (opcode & 0x00ff) >> 0); return buf;
        case 0x8f00: dst += sprintf(dst, "%-7s %+i", "bf/s", (opcode & 0x00ff) >> 0); return buf;
        case 0x8900: dst += sprintf(dst, "%-7s %+i", "bt", (opcode & 0x00ff) >> 0); return buf;
        case 0x8d00: dst += sprintf(dst, "%-7s %+i", "bt/s", (opcode & 0x00ff) >> 0); return buf;
        case 0xc300: dst += sprintf(dst, "%-7s #0x%02x", "trapa", (opcode & 0x00ff) >> 0); return buf;
    }

    switch (opcode & 0xf0ff) {
        case 0x0029: dst += sprintf(dst, "%-7s R%u", "movt", (opcode & 0x0f00) >> 8); return buf;
        case 0x4015: dst += sprintf(dst, "%-7s R%u", "cmp/pl", (opcode & 0x0f00) >> 8); return buf;
        case 0x4011: dst += sprintf(dst, "%-7s R%u", "cmp/pz", (opcode & 0x0f00) >> 8); return buf;
        case 0x4010: dst += sprintf(dst, "%-7s R%u", "dt", (opcode & 0x0f00) >> 8); return buf;
        case 0x401b: dst += sprintf(dst, "%-7s @R%u", "tas.b", (opcode & 0x0f00) >> 8); return buf;
        case 0x4024: dst += sprintf(dst, "%-7s R%u", "rotcl", (opcode & 0x0f00) >> 8); return buf;
        case 0x4025: dst += sprintf(dst, "%-7s R%u", "rotcr", (opcode & 0x0f00) >> 8); return buf;
        case 0x4004: dst += sprintf(dst, "%-7s R%u", "rotl", (opcode & 0x0f00) >> 8); return buf;
        case 0x4005: dst += sprintf(dst, "%-7s R%u", "rotr", (opcode & 0x0f00) >> 8); return buf;
        case 0x4020: dst += sprintf(dst, "%-7s R%u", "shal", (opcode & 0x0f00) >> 8); return buf;
        case 0x4021: dst += sprintf(dst, "%-7s R%u", "shar", (opcode & 0x0f00) >> 8); return buf;
        case 0x4000: dst += sprintf(dst, "%-7s R%u", "shll", (opcode & 0x0f00) >> 8); return buf;
        case 0x4008: dst += sprintf(dst, "%-7s R%u", "shll2", (opcode & 0x0f00) >> 8); return buf;
        case 0x4018: dst += sprintf(dst, "%-7s R%u", "shll8", (opcode & 0x0f00) >> 8); return buf;
        case 0x4028: dst += sprintf(dst, "%-7s R%u", "shll16", (opcode & 0x0f00) >> 8); return buf;
        case 0x4001: dst += sprintf(dst, "%-7s R%u", "shlr", (opcode & 0x0f00) >> 8); return buf;
        case 0x4009: dst += sprintf(dst, "%-7s R%u", "shlr2", (opcode & 0x0f00) >> 8); return buf;
        case 0x4019: dst += sprintf(dst, "%-7s R%u", "shlr8", (opcode & 0x0f00) >> 8); return buf;
        case 0x4029: dst += sprintf(dst, "%-7s R%u", "shlr16", (opcode & 0x0f00) >> 8); return buf;
        case 0x0023: dst += sprintf(dst, "%-7s R%u", "braf", (opcode & 0x0f00) >> 8); return buf;
        case 0x0003: dst += sprintf(dst, "%-7s R%u", "bsrf", (opcode & 0x0f00) >> 8); return buf;
        case 0x402b: dst += sprintf(dst, "%-7s @R%u", "jmp", (opcode & 0x0f00) >> 8); return buf;
        case 0x400b: dst += sprintf(dst, "%-7s @R%u", "jsr", (opcode & 0x0f00) >> 8); return buf;
        case 0x400e: dst += sprintf(dst, "%-7s R%u, SR", "ldc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4007: dst += sprintf(dst, "%-7s @R%u+, SR", "ldc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x401e: dst += sprintf(dst, "%-7s R%u, GBR", "ldc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4017: dst += sprintf(dst, "%-7s @R%u+, GBR", "ldc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x402e: dst += sprintf(dst, "%-7s R%u, VBR", "ldc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4027: dst += sprintf(dst, "%-7s @R%u+, VBR", "ldc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x403e: dst += sprintf(dst, "%-7s R%u, SSR", "ldc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4037: dst += sprintf(dst, "%-7s @R%u+, SSR", "ldc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x404e: dst += sprintf(dst, "%-7s R%u, SPC", "ldc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4047: dst += sprintf(dst, "%-7s @R%u+, SPC", "ldc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x40fa: dst += sprintf(dst, "%-7s R%u, DBR", "ldc", (opcode & 0x0f00) >> 8); return buf;
        case 0x40f6: dst += sprintf(dst, "%-7s @R%u+, DBR", "ldc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x400a: dst += sprintf(dst, "%-7s R%u, MACH", "lds", (opcode & 0x0f00) >> 8); return buf;
        case 0x4006: dst += sprintf(dst, "%-7s @R%u+, MACH", "lds.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x401a: dst += sprintf(dst, "%-7s R%u, MACL", "lds", (opcode & 0x0f00) >> 8); return buf;
        case 0x4016: dst += sprintf(dst, "%-7s @R%u+, MACL", "lds.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x402a: dst += sprintf(dst, "%-7s R%u, PR", "lds", (opcode & 0x0f00) >> 8); return buf;
        case 0x4026: dst += sprintf(dst, "%-7s @R%u+, PR", "lds.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x00c3: dst += sprintf(dst, "%-7s R0, @R%u", "movca.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x0093: dst += sprintf(dst, "%-7s @R%u", "ocbi", (opcode & 0x0f00) >> 8); return buf;
        case 0x00a3: dst += sprintf(dst, "%-7s @R%u", "ocbp", (opcode & 0x0f00) >> 8); return buf;
        case 0x00b3: dst += sprintf(dst, "%-7s @R%u", "ocbwb", (opcode & 0x0f00) >> 8); return buf;
        case 0x0083: dst += sprintf(dst, "%-7s @R%u", "pref", (opcode & 0x0f00) >> 8); return buf;
        case 0x0002: dst += sprintf(dst, "%-7s SR, R%u", "stc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4003: dst += sprintf(dst, "%-7s SR, @-R%u", "stc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x0012: dst += sprintf(dst, "%-7s GBR, R%u", "stc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4013: dst += sprintf(dst, "%-7s GBR, @-R%u", "stc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x0022: dst += sprintf(dst, "%-7s VBR, R%u", "stc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4023: dst += sprintf(dst, "%-7s VBR, @-R%u", "stc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x003a: dst += sprintf(dst, "%-7s SGR, R%u", "stc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4032: dst += sprintf(dst, "%-7s SGR, @-R%u", "stc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x0032: dst += sprintf(dst, "%-7s SSR, R%u", "stc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4033: dst += sprintf(dst, "%-7s SSR, @-R%u", "stc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x0042: dst += sprintf(dst, "%-7s SPC, R%u", "stc", (opcode & 0x0f00) >> 8); return buf;
        case 0x4043: dst += sprintf(dst, "%-7s SPC, @-R%u", "stc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x00fa: dst += sprintf(dst, "%-7s DBR, R%u", "stc", (opcode & 0x0f00) >> 8); return buf;
        case 0x40f2: dst += sprintf(dst, "%-7s DBR, @-R%u", "stc.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x000a: dst += sprintf(dst, "%-7s MACH, R%u", "sts", (opcode & 0x0f00) >> 8); return buf;
        case 0x4002: dst += sprintf(dst, "%-7s MACH, @-R%u", "sts.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x001a: dst += sprintf(dst, "%-7s MACL, R%u", "sts", (opcode & 0x0f00) >> 8); return buf;
        case 0x4012: dst += sprintf(dst, "%-7s MACL, @-R%u", "sts.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x002a: dst += sprintf(dst, "%-7s PR, R%u", "sts", (opcode & 0x0f00) >> 8); return buf;
        case 0x4022: dst += sprintf(dst, "%-7s PR, @-R%u", "sts.l", (opcode & 0x0f00) >> 8); return buf;
        case 0xf08d: dst += sprintf(dst, "%-7s FR%u", "fldi0", (opcode & 0x0f00) >> 8); return buf;
        case 0xf09d: dst += sprintf(dst, "%-7s FR%u", "fldi1", (opcode & 0x0f00) >> 8); return buf;
        case 0xf01d: dst += sprintf(dst, "%-7s FR%u, FPUL", "flds", (opcode & 0x0f00) >> 8); return buf;
        case 0xf00d: dst += sprintf(dst, "%-7s FPUL, FR%u", "fsts", (opcode & 0x0f00) >> 8); return buf;
        case 0xf05d: dst += sprintf(dst, "%-7s FR%u", "fabs", (opcode & 0x0f00) >> 8); return buf;
        case 0xf04d: dst += sprintf(dst, "%-7s FR%u", "fneg", (opcode & 0x0f00) >> 8); return buf;
        case 0xf06d: dst += sprintf(dst, "%-7s FR%u", "fsqrt", (opcode & 0x0f00) >> 8); return buf;
        case 0xf02d: dst += sprintf(dst, "%-7s FPUL, FR%u", "float", (opcode & 0x0f00) >> 8); return buf;
        case 0xf03d: dst += sprintf(dst, "%-7s FR%u, FPUL", "ftrc", (opcode & 0x0f00) >> 8); return buf;
        case 0xf0ed: dst += sprintf(dst, "%-7s FVm, FVn", "fipr"); return buf;
        case 0x406a: dst += sprintf(dst, "%-7s R%u, FPSCR", "lds", (opcode & 0x0f00) >> 8); return buf;
        case 0x006a: dst += sprintf(dst, "%-7s FPSCR, R%u", "sts", (opcode & 0x0f00) >> 8); return buf;
        case 0x4066: dst += sprintf(dst, "%-7s @R%u+, FPSCR", "lds.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x4062: dst += sprintf(dst, "%-7s FPSCR, @-R%u", "sts.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x405a: dst += sprintf(dst, "%-7s R%u, FPUL", "lds", (opcode & 0x0f00) >> 8); return buf;
        case 0x005a: dst += sprintf(dst, "%-7s FPUL, R%u", "sts", (opcode & 0x0f00) >> 8); return buf;
        case 0x4056: dst += sprintf(dst, "%-7s @R%u+, FPUL", "lds.l", (opcode & 0x0f00) >> 8); return buf;
        case 0x4052: dst += sprintf(dst, "%-7s FPUL, @-R%u", "sts.l", (opcode & 0x0f00) >> 8); return buf;
    }

    switch (opcode & 0xffff) {
        case 0x0019: dst += sprintf(dst, "%s\n", "div0u"); return buf;
        case 0x000b: dst += sprintf(dst, "%s\n", "rts"); return buf;
        case 0x0028: dst += sprintf(dst, "%s\n", "clrmac"); return buf;
        case 0x0048: dst += sprintf(dst, "%s\n", "clrs"); return buf;
        case 0x0008: dst += sprintf(dst, "%s\n", "clrt"); return buf;
        case 0x0038: dst += sprintf(dst, "%s\n", "ldtlb"); return buf;
        case 0x0009: dst += sprintf(dst, "%s\n", "nop"); return buf;
        case 0x002b: dst += sprintf(dst, "%s\n", "rte"); return buf;
        case 0x0058: dst += sprintf(dst, "%s\n", "sets"); return buf;
        case 0x0018: dst += sprintf(dst, "%s\n", "sett"); return buf;
        case 0x001b: dst += sprintf(dst, "%s\n", "sleep"); return buf;
        case 0xfbfd: dst += sprintf(dst, "%s\n", "frchg"); return buf;
        case 0xf3fd: dst += sprintf(dst, "%s\n", "fschg"); return buf;
    }

    switch (opcode & 0xf08f) {
        case 0x408e: dst += sprintf(dst, "%-7s R%u, R%u_BANK", "ldc", (opcode & 0x0f00) >> 8, (opcode & 0x0070) >> 4); return buf;
        case 0x4087: dst += sprintf(dst, "%-7s @R%u+, R%u_BANK", "ldc.l", (opcode & 0x0f00) >> 8, (opcode & 0x0070) >> 4); return buf;
        case 0x0082: dst += sprintf(dst, "%-7s R%u_BANK, R%u", "stc", (opcode & 0x0070) >> 4, (opcode & 0x0f00) >> 8); return buf;
        case 0x4083: dst += sprintf(dst, "%-7s R%u_BANK, @-R%u", "stc.l", (opcode & 0x0070) >> 4, (opcode & 0x0f00) >> 8); return buf;
    }

    switch (opcode & 0xf11f) {
        case 0xf00c: dst += sprintf(dst, "%-7s DR%u, DR%u", "fmov", (opcode & 0x00e0) >> 5, (opcode & 0x0e00) >> 9); return buf;
        case 0xf10c: dst += sprintf(dst, "%-7s DR%u, XDn", "fmov", (opcode & 0x00e0) >> 5); return buf;
        case 0xf01c: dst += sprintf(dst, "%-7s XDm, DR%u", "fmov", (opcode & 0x0e00) >> 9); return buf;
        case 0xf11c: dst += sprintf(dst, "%-7s XDm, XDn", "fmov"); return buf;
        case 0xf000: dst += sprintf(dst, "%-7s DR%u, DR%u", "fadd", (opcode & 0x00e0) >> 5, (opcode & 0x0e00) >> 9); return buf;
        case 0xf001: dst += sprintf(dst, "%-7s DR%u, DR%u", "fsub", (opcode & 0x00e0) >> 5, (opcode & 0x0e00) >> 9); return buf;
        case 0xf002: dst += sprintf(dst, "%-7s DR%u, DR%u", "fmul", (opcode & 0x00e0) >> 5, (opcode & 0x0e00) >> 9); return buf;
        case 0xf003: dst += sprintf(dst, "%-7s DR%u, DR%u", "fdiv", (opcode & 0x00e0) >> 5, (opcode & 0x0e00) >> 9); return buf;
        case 0xf004: dst += sprintf(dst, "%-7s DR%u, DR%u", "fcmp/eq", (opcode & 0x00e0) >> 5, (opcode & 0x0e00) >> 9); return buf;
        case 0xf005: dst += sprintf(dst, "%-7s DR%u, DR%u", "fcmp/gt", (opcode & 0x00e0) >> 5, (opcode & 0x0e00) >> 9); return buf;
    }

    switch (opcode & 0xf10f) {
        case 0xf008: dst += sprintf(dst, "%-7s @R%u, DR%u", "fmov.d", (opcode & 0x00f0) >> 4, (opcode & 0x0e00) >> 9); return buf;
        case 0xf108: dst += sprintf(dst, "%-7s @R%u, XDn", "fmov.d", (opcode & 0x00f0) >> 4); return buf;
        case 0xf009: dst += sprintf(dst, "%-7s @R%u+, DR%u", "fmov.d", (opcode & 0x00f0) >> 4, (opcode & 0x0e00) >> 9); return buf;
        case 0xf109: dst += sprintf(dst, "%-7s @R%u+, XDn", "fmov.d", (opcode & 0x00f0) >> 4); return buf;
        case 0xf006: dst += sprintf(dst, "%-7s @(R0,R%u), DR%u", "fmov.d", (opcode & 0x00f0) >> 4, (opcode & 0x0e00) >> 9); return buf;
        case 0xf106: dst += sprintf(dst, "%-7s @(R0,R%u), XDn", "fmov.d", (opcode & 0x00f0) >> 4); return buf;
    }

    switch (opcode & 0xf01f) {
        case 0xf00a: dst += sprintf(dst, "%-7s DR%u, @R%u", "fmov.d", (opcode & 0x00e0) >> 5, (opcode & 0x0f00) >> 8); return buf;
        case 0xf01a: dst += sprintf(dst, "%-7s XDm, @R%u", "fmov.d", (opcode & 0x0f00) >> 8); return buf;
        case 0xf00b: dst += sprintf(dst, "%-7s DR%u, @-R%u", "fmov.d", (opcode & 0x00e0) >> 5, (opcode & 0x0f00) >> 8); return buf;
        case 0xf01b: dst += sprintf(dst, "%-7s XDm, @-R%u", "fmov.d", (opcode & 0x0f00) >> 8); return buf;
        case 0xf007: dst += sprintf(dst, "%-7s DR%u, @(R0,R%u)", "fmov.d", (opcode & 0x00e0) >> 5, (opcode & 0x0f00) >> 8); return buf;
        case 0xf017: dst += sprintf(dst, "%-7s XDm, @(R0,R%u)", "fmov.d", (opcode & 0x0f00) >> 8); return buf;
    }

    switch (opcode & 0xf3ff) {
        case 0xf1fd: dst += sprintf(dst, "%-7s XMTRX, FVn", "ftrv"); return buf;
    }

    switch (opcode & 0xf1ff) {
        case 0xf05d: dst += sprintf(dst, "%-7s DR%u", "fabs", (opcode & 0x0e00) >> 9); return buf;
        case 0xf04d: dst += sprintf(dst, "%-7s DR%u", "fneg", (opcode & 0x0e00) >> 9); return buf;
        case 0xf06d: dst += sprintf(dst, "%-7s DR%u", "fsqrt", (opcode & 0x0e00) >> 9); return buf;
        case 0xf02d: dst += sprintf(dst, "%-7s FPUL, DR%u", "float", (opcode & 0x0e00) >> 9); return buf;
        case 0xf03d: dst += sprintf(dst, "%-7s DR%u, FPUL", "ftrc", (opcode & 0x0e00) >> 9); return buf;
        case 0xf0bd: dst += sprintf(dst, "%-7s DR%u, FPUL", "fcnvds", (opcode & 0x0e00) >> 9); return buf;
        case 0xf0ad: dst += sprintf(dst, "%-7s FPUL, DR%u", "fcnvsd", (opcode & 0x0e00) >> 9); return buf;
    }

    dst += sprintf(dst, "<invalid>");

    return buf;
}