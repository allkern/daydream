#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sh4.h"

sh4_state* sh4_create(void) {
    return malloc(sizeof(sh4_state));
}

void sh4_init(sh4_state* cpu, sh4_bus bus) {
    memset(cpu, 0, sizeof(sh4_state));

    cpu->sr.u32 = 0x700000f0;
    cpu->pc = 0xa0000000;
    cpu->bus = bus;
}

void sh4_ex_group2(sh4_state* cpu) {
    switch (cpu->opcode & 0xf) {
        case 0:
        case 1:
        case 2: {
            uint32_t addr = sh4_get_reg(cpu, (cpu->opcode >> 8) & 0xf);
            uint32_t data = sh4_get_reg(cpu, (cpu->opcode >> 4) & 0xf);

            cpu->bus.write32(cpu->bus.udata, addr, data);

            printf("%08x: %04x %-7s R%u, @R%u\n",
                cpu->pc,
                opcode,
                "mov.l",
                (opcode >> 8) & 0xf,
                (opcode >> 4) & 0xf
            );
        } break;
    }
}

void sh4_cycle(sh4_state* cpu) {
    cpu->opcode = cpu->bus.read16(cpu->bus.udata, cpu->pc);

    switch (field1) {
        case 2: sh4_ex_group2(cpu); break;

        case 13: {
            uint32_t disp = opcode & 0xff;
            uint32_t addr = (cpu->pc & 0xFFFFFFFC) + 4 + (disp << 2);
            uint32_t data = cpu->bus.read32(cpu->bus.udata, addr);

            sh4_set_reg(cpu, (opcode >> 8) & 0xf, data);

            printf("%08x: %04x %-7s @(%02x,PC), R%u ; %08x (%08x)\n",
                cpu->pc,
                opcode,
                "mov.l",
                disp,
                (opcode >> 8) & 0xf,
                addr,
                data
            );
        } break;

        case 14: {
            uint32_t data = (int32_t)((opcode & 0xff) << 24) >> 24;

            sh4_set_reg(cpu, (opcode >> 8) & 0xf, data);

            printf("%08x: %04x %-7s #%i, R%u\n",
                cpu->pc,
                opcode,
                "mov",
                data,
                (opcode >> 8) & 0xf
            );
        } break;

        default: {
            printf("%08x: %04x <unimplemented>\n",
                cpu->pc,
                opcode
            );
        } break;
    }

    cpu->pc += 2;
}

void sh4_destroy(sh4_state* cpu) {
    free(cpu);
}

uint32_t sh4_get_reg(sh4_state* cpu, int index) {
    if (index < 8)
        return cpu->rb[cpu->sr.rb && cpu->sr.md][index];

    return cpu->r[index - 8];
}

void sh4_set_reg(sh4_state* cpu, int index, uint32_t value) {
    if (index < 8) {
        cpu->rb[cpu->sr.rb && cpu->sr.md][index] = value;

        return;
    }

    cpu->r[index - 8] = value;
}