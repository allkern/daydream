#ifndef BUS_H
#define BUS_H

#include "ram.h"

typedef struct {
    ram_state* ram;
} dc_bus_state;

dc_bus_state* dc_bus_create(void);
void dc_bus_init(dc_bus_state* bus);
uint32_t dc_bus_read8(dc_bus_state* bus, uint32_t addr);
uint32_t dc_bus_read16(dc_bus_state* bus, uint32_t addr);
uint32_t dc_bus_read32(dc_bus_state* bus, uint32_t addr);
void dc_bus_write8(dc_bus_state* bus, uint32_t addr, uint32_t data);
void dc_bus_write16(dc_bus_state* bus, uint32_t addr, uint32_t data);
void dc_bus_write32(dc_bus_state* bus, uint32_t addr, uint32_t data);
void dc_bus_destroy(dc_bus_state* bus);

#endif