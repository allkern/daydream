#ifndef SH4_DIS_H
#define SH4_DIS_H

#include <stdint.h>

typedef struct {
    uint32_t pc;
    int print_address;
    int print_opcode;
} sh4d_state;

char* sh4_disassemble(uint16_t opcode, char* buf, sh4d_state* state);

#endif