#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "holly.h"

holly_state* holly_create() {
    return (holly_state*)malloc(sizeof(holly_state));
}

void holly_init(holly_state* holly, size_t size) {
    memset(holly, 0, sizeof(holly_state));

    holly->buf = malloc(size);
}

uint32_t holly_read32(void* udata, uint32_t addr) {
    holly_state* holly = (holly_state*)udata;

    if (addr >= 0x800000)
        return 0xffffffff;

    return *(uint32_t*)(&holly->buf[addr & 0x7fffff]);
}

uint32_t holly_read16(void* udata, uint32_t addr) {
    holly_state* holly = (holly_state*)udata;

    if (addr >= 0x800000)
        return 0xffffffff;

    return *(uint16_t*)(&holly->buf[addr & 0x7fffff]);
}

uint32_t holly_read8(void* udata, uint32_t addr) {
    holly_state* holly = (holly_state*)udata;

    if (addr >= 0x800000)
        return 0xffffffff;

    return *(uint8_t*)(&holly->buf[addr & 0x7fffff]);
}

void holly_write32(void* udata, uint32_t addr, uint32_t data) {
    holly_state* holly = (holly_state*)udata;

    // if (addr >= 0x800000)
    //     return;

    *(uint32_t*)(&holly->buf[addr & 0x7fffff]) = data;
}

void holly_write16(void* udata, uint32_t addr, uint32_t data) {
    holly_state* holly = (holly_state*)udata;

    // if (addr >= 0x800000)
    //     return;

    *(uint16_t*)(&holly->buf[addr & 0x7fffff]) = data;
}

void holly_write8(void* udata, uint32_t addr, uint32_t data) {
    holly_state* holly = (holly_state*)udata;

    // if (addr >= 0x800000)
    //     return;

    *(uint8_t*)(&holly->buf[addr & 0x7fffff]) = data;
}

void holly_destroy(holly_state* holly) {
    free(holly->buf);
    free(holly);
}