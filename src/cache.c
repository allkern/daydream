#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "cache.h"

int cache_get_addr(cache_state* cache, uint32_t* addr) {
    // ORA
    if (!(cache->p4->ccr & 0x20))
        return 0;

    // OIX
    if (cache->p4->ccr & 0x80) {
        *addr = ((*addr & 0x2000) >> 1) | (*addr & 0xfff);
    } else {
        *addr = ((*addr & 0x2000000) >> 13) | (*addr & 0xfff);
    }

    return 1;
}

cache_state* cache_create() {
    return (cache_state*)malloc(sizeof(cache_state));
}

void cache_init(cache_state* cache, p4_state* p4) {
    memset(cache, 0, sizeof(cache_state));

    cache->buf = malloc(0x2000);
    cache->p4 = p4;
}

uint32_t cache_read32(void* udata, uint32_t addr) {
    cache_state* cache = (cache_state*)udata;

    if (!cache_get_addr(cache, &addr))
        return 0xffffffff;

    return *(uint32_t*)(&cache->buf[addr]);
}

uint32_t cache_read16(void* udata, uint32_t addr) {
    cache_state* cache = (cache_state*)udata;

    if (!cache_get_addr(cache, &addr))
        return 0xffffffff;

    return *(uint16_t*)(&cache->buf[addr]);
}

uint32_t cache_read8(void* udata, uint32_t addr) {
    cache_state* cache = (cache_state*)udata;

    if (!cache_get_addr(cache, &addr))
        return 0xffffffff;

    return *(uint8_t*)(&cache->buf[addr]);
}

void cache_write32(void* udata, uint32_t addr, uint32_t data) {
    cache_state* cache = (cache_state*)udata;

    if (!cache_get_addr(cache, &addr))
        return;

    *(uint32_t*)(&cache->buf[addr]) = data;
}

void cache_write16(void* udata, uint32_t addr, uint32_t data) {
    cache_state* cache = (cache_state*)udata;

    if (!cache_get_addr(cache, &addr))
        return;

    *(uint16_t*)(&cache->buf[addr]) = data;
}

void cache_write8(void* udata, uint32_t addr, uint32_t data) {
    cache_state* cache = (cache_state*)udata;

    if (!cache_get_addr(cache, &addr))
        return;

    *(uint8_t*)(&cache->buf[addr]) = data;
}

void cache_destroy(cache_state* cache) {
    free(cache->buf);
    free(cache);
}