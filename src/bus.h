#ifndef BUS_H
#define BUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "boot.h"
#include "cache.h"
#include "flash.h"
#include "p4.h"
#include "ram.h"
#include "vram.h"
#include "holly/pvr2.h"

typedef struct {
    boot_state* boot;
    cache_state* cache;
    flash_state* flash;
    p4_state* p4;
    ram_state* ram;
    vram_state* vram;
    pvr2_state* pvr2;
} dc_bus_state;

dc_bus_state* dc_bus_create(void);
void dc_bus_init(dc_bus_state* bus, const char* boot, const char* flash);
uint32_t dc_bus_read8(dc_bus_state* bus, uint32_t addr);
uint32_t dc_bus_read16(dc_bus_state* bus, uint32_t addr);
uint32_t dc_bus_read32(dc_bus_state* bus, uint32_t addr);
void dc_bus_write8(dc_bus_state* bus, uint32_t addr, uint32_t data);
void dc_bus_write16(dc_bus_state* bus, uint32_t addr, uint32_t data);
void dc_bus_write32(dc_bus_state* bus, uint32_t addr, uint32_t data);
void dc_bus_destroy(dc_bus_state* bus);

#ifdef __cplusplus
}
#endif

#endif