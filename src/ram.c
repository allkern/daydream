#include "ram.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

ram_state* ram_create() {
    return (ram_state*)malloc(sizeof(ram_state));
}

void ram_init(ram_state* ram, size_t size) {
    memset(ram, 0, sizeof(ram_state));

    ram->buf = malloc(size);
}

uint32_t ram_read32(void* udata, uint32_t addr) {
    ram_state* ram = (ram_state*)udata;

    return *(uint32_t*)(&ram->buf[addr]);
}

uint32_t ram_read16(void* udata, uint32_t addr) {
    ram_state* ram = (ram_state*)udata;

    return *(uint16_t*)(&ram->buf[addr]);
}

uint32_t ram_read8(void* udata, uint32_t addr) {
    ram_state* ram = (ram_state*)udata;

    return *(uint8_t*)(&ram->buf[addr]);
}

void ram_write32(void* udata, uint32_t addr, uint32_t data) {
    ram_state* ram = (ram_state*)udata;

    *(uint32_t*)(&ram->buf[addr]) = data;
}

void ram_write16(void* udata, uint32_t addr, uint32_t data) {
    ram_state* ram = (ram_state*)udata;

    *(uint16_t*)(&ram->buf[addr]) = data;
}

void ram_write8(void* udata, uint32_t addr, uint32_t data) {
    ram_state* ram = (ram_state*)udata;

    *(uint8_t*)(&ram->buf[addr]) = data;
}

void ram_load(ram_state* ram, const char* path, uint32_t addr) {
    FILE* file = fopen(path, "rb");

    if (!file) {
        printf("Couldn't open file \'%s\'\n", path);

        return;
    }

    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);

    fseek(file, 0, SEEK_SET);

    fread(ram->buf + addr, 1, size, file);
    fclose(file);
}

void ram_destroy(ram_state* ram) {
    free(ram->buf);
    free(ram);
}