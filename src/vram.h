#ifndef VRAM_H
#define VRAM_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t* buf;
} vram_state;

vram_state* vram_create();
void vram_init(vram_state* vram, size_t size);
uint32_t vram_read32(void* udata, uint32_t addr);
uint32_t vram_read16(void* udata, uint32_t addr);
uint32_t vram_read8(void* udata, uint32_t addr);
void vram_write32(void* udata, uint32_t addr, uint32_t data);
void vram_write16(void* udata, uint32_t addr, uint32_t data);
void vram_write8(void* udata, uint32_t addr, uint32_t data);
void vram_destroy(vram_state* vram);

#endif