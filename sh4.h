#ifndef SH4_H
#define SH4_H

#include <stdint.h>

#define SR_T     0x00000001
#define SR_S     0x00000002
#define SR_IMASK 0x000000f0
#define SR_Q     0x00000100
#define SR_M     0x00000200
#define SR_FD    0x00008000
#define SR_BL    0x10000000
#define SR_RB    0x20000000
#define SR_MD    0x40000000

typedef uint32_t (*sh4_bus_read8_func)(void*, uint32_t);
typedef uint32_t (*sh4_bus_read16_func)(void*, uint32_t);
typedef uint32_t (*sh4_bus_read32_func)(void*, uint32_t);
typedef void (*sh4_bus_write8_func)(void*, uint32_t, uint32_t);
typedef void (*sh4_bus_write16_func)(void*, uint32_t, uint32_t);
typedef void (*sh4_bus_write32_func)(void*, uint32_t, uint32_t);

typedef struct {
    void* udata;
    sh4_bus_read8_func read8;
    sh4_bus_read16_func read16;
    sh4_bus_read32_func read32;
    sh4_bus_write8_func write8;
    sh4_bus_write16_func write16;
    sh4_bus_write32_func write32;
} sh4_bus;

typedef struct {
    sh4_bus bus;
    uint32_t rb[2][8];
    uint32_t r[8];

    union {
        uint32_t u32;

        struct {
            unsigned int t     : 1;
            unsigned int s     : 1;
            unsigned int res0  : 2;
            unsigned int imask : 4;
            unsigned int q     : 1;
            unsigned int m     : 1;
            unsigned int res1  : 5;
            unsigned int fd    : 1;
            unsigned int res2  : 12;
            unsigned int bl    : 1;
            unsigned int rb    : 1;
            unsigned int md    : 1;
            unsigned int res3  : 1;
        };
    } sr;

    uint32_t ssr;
    uint32_t gbr;
    uint32_t mach;
    uint32_t macl;
    uint32_t pr;
    uint32_t vbr;
    uint32_t pc;
    uint32_t spc;
    uint32_t sgr;
    uint32_t dbr;
    uint32_t opcode;
} sh4_state;

sh4_state* sh4_create(void);
void sh4_init(sh4_state* cpu, sh4_bus bus);
void sh4_cycle(sh4_state* cpu);
void sh4_destroy(sh4_state* cpu);
uint32_t sh4_get_reg(sh4_state* cpu, int index);
void sh4_set_reg(sh4_state* cpu, int index, uint32_t value);

#endif