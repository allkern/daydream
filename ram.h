#ifndef RAM_H
#define RAM_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t* buf;
} ram_state;

ram_state* ram_create();
void ram_init(ram_state* ram, size_t size);
uint32_t ram_read32(void* udata, uint32_t addr);
uint32_t ram_read16(void* udata, uint32_t addr);
uint32_t ram_read8(void* udata, uint32_t addr);
void ram_write32(void* udata, uint32_t addr, uint32_t data);
void ram_write16(void* udata, uint32_t addr, uint32_t data);
void ram_write8(void* udata, uint32_t addr, uint32_t data);
void ram_load(ram_state* ram, const char* path, uint32_t addr);
void ram_destroy(ram_state* ram);

#endif