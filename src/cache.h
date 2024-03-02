#ifndef CACHE_H
#define CACHE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

#include "p4.h"

typedef struct {
    uint8_t* buf;
    p4_state* p4;
} cache_state;

cache_state* cache_create();
void cache_init(cache_state* cache, p4_state* p4);
uint32_t cache_read32(void* udata, uint32_t addr);
uint32_t cache_read16(void* udata, uint32_t addr);
uint32_t cache_read8(void* udata, uint32_t addr);
void cache_write32(void* udata, uint32_t addr, uint32_t data);
void cache_write16(void* udata, uint32_t addr, uint32_t data);
void cache_write8(void* udata, uint32_t addr, uint32_t data);
void cache_destroy(cache_state* cache);

#ifdef __cplusplus
}
#endif

#endif