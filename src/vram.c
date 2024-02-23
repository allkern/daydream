#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "vram.h"

vram_state* vram_create() {
    return (vram_state*)malloc(sizeof(vram_state));
}

void vram_init(vram_state* vram, size_t size) {
    memset(vram, 0, sizeof(vram_state));

    vram->buf = malloc(size);
}

uint32_t vram_read32(void* udata, uint32_t addr) {
    vram_state* vram = (vram_state*)udata;

    if (addr >= 0x800000)
        return 0xffffffff;

    return *(uint32_t*)(&vram->buf[addr & 0x7fffff]);
}

uint32_t vram_read16(void* udata, uint32_t addr) {
    vram_state* vram = (vram_state*)udata;

    if (addr >= 0x800000)
        return 0xffffffff;

    return *(uint16_t*)(&vram->buf[addr & 0x7fffff]);
}

uint32_t vram_read8(void* udata, uint32_t addr) {
    vram_state* vram = (vram_state*)udata;

    if (addr >= 0x800000)
        return 0xffffffff;

    return *(uint8_t*)(&vram->buf[addr & 0x7fffff]);
}

void vram_write32(void* udata, uint32_t addr, uint32_t data) {
    vram_state* vram = (vram_state*)udata;

    // printf("VRAM 32-bit write addr=%08x data=%08x\n", addr & 0x7fffff, data);

    // if (addr >= 0x800000)
    //     return;

    *(uint32_t*)(&vram->buf[addr & 0x7fffff]) = data;
}

void vram_write16(void* udata, uint32_t addr, uint32_t data) {
    vram_state* vram = (vram_state*)udata;

    // if (addr >= 0x800000)
    //     return;

    *(uint16_t*)(&vram->buf[addr & 0x7fffff]) = data;
}

void vram_write8(void* udata, uint32_t addr, uint32_t data) {
    vram_state* vram = (vram_state*)udata;

    // if (addr >= 0x800000)
    //     return;

    *(uint8_t*)(&vram->buf[addr & 0x7fffff]) = data;
}

void vram_destroy(vram_state* vram) {
    free(vram->buf);
    free(vram);
}