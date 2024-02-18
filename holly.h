#ifndef HOLLY_H
#define HOLLY_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t* buf;
} holly_state;

holly_state* holly_create();
void holly_init(holly_state* holly, size_t size);
uint32_t holly_read32(void* udata, uint32_t addr);
uint32_t holly_read16(void* udata, uint32_t addr);
uint32_t holly_read8(void* udata, uint32_t addr);
void holly_write32(void* udata, uint32_t addr, uint32_t data);
void holly_write16(void* udata, uint32_t addr, uint32_t data);
void holly_write8(void* udata, uint32_t addr, uint32_t data);
void holly_destroy(holly_state* holly);

#endif