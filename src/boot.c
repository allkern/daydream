#include "boot.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

boot_state* boot_create() {
    return (boot_state*)malloc(sizeof(boot_state));
}

void boot_init(boot_state* boot, const char* path) {
    memset(boot, 0, sizeof(boot_state));

    boot->buf = malloc(0x200000);

    FILE* file = fopen(path, "rb");

    fread(boot->buf, 1, 0x200000, file);
    fclose(file);

    uint16_t* buf = (uint16_t*)boot->buf;
}

uint32_t boot_read32(void* udata, uint32_t addr) {
    boot_state* boot = (boot_state*)udata;

    return *(uint32_t*)(&boot->buf[addr]);
}

uint32_t boot_read16(void* udata, uint32_t addr) {
    boot_state* boot = (boot_state*)udata;

    return *(uint16_t*)(&boot->buf[addr]);
}

uint32_t boot_read8(void* udata, uint32_t addr) {
    boot_state* boot = (boot_state*)udata;

    return *(uint8_t*)(&boot->buf[addr]);
}

void boot_write32(void* udata, uint32_t addr, uint32_t data) {
    boot_state* boot = (boot_state*)udata;

    *(uint32_t*)(&boot->buf[addr]) = data;
}

void boot_write16(void* udata, uint32_t addr, uint32_t data) {
    boot_state* boot = (boot_state*)udata;

    *(uint16_t*)(&boot->buf[addr]) = data;
}

void boot_write8(void* udata, uint32_t addr, uint32_t data) {
    boot_state* boot = (boot_state*)udata;

    *(uint8_t*)(&boot->buf[addr]) = data;
}

void boot_destroy(boot_state* boot) {
    free(boot->buf);
    free(boot);
}