#include "flash.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

flash_state* flash_create() {
    return (flash_state*)malloc(sizeof(flash_state));
}

void flash_init(flash_state* flash, const char* path) {
    memset(flash, 0, sizeof(flash_state));

    flash->buf = malloc(0x40000);

    FILE* file = fopen(path, "rb");

    fread(flash->buf, 1, 0x40000, file);
    fclose(file);
}

uint32_t flash_read32(void* udata, uint32_t addr) {
    flash_state* flash = (flash_state*)udata;

    return *(uint32_t*)(&flash->buf[addr]);
}

uint32_t flash_read16(void* udata, uint32_t addr) {
    flash_state* flash = (flash_state*)udata;

    return *(uint16_t*)(&flash->buf[addr]);
}

uint32_t flash_read8(void* udata, uint32_t addr) {
    flash_state* flash = (flash_state*)udata;

    return *(uint8_t*)(&flash->buf[addr]);
}

void flash_write32(void* udata, uint32_t addr, uint32_t data) {
    flash_state* flash = (flash_state*)udata;

    *(uint32_t*)(&flash->buf[addr]) = data;
}

void flash_write16(void* udata, uint32_t addr, uint32_t data) {
    flash_state* flash = (flash_state*)udata;

    *(uint16_t*)(&flash->buf[addr]) = data;
}

void flash_write8(void* udata, uint32_t addr, uint32_t data) {
    flash_state* flash = (flash_state*)udata;

    *(uint8_t*)(&flash->buf[addr]) = data;
}

void flash_destroy(flash_state* flash) {
    free(flash->buf);
    free(flash);
}