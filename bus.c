#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bus.h"

/*
    0x04000000-0x07FFFFFF 	Video RAM (8MB) 	Area 1
    0x0C000000-0x0FFFFFFF 	System RAM (16MB) 	Area 3
*/

dc_bus_state* dc_bus_create(void) {
    return malloc(sizeof(dc_bus_state));
}

void dc_bus_init(dc_bus_state* bus) {
    bus->ram = ram_create();
    bus->holly = holly_create();

    ram_init(bus->ram, 0x1000000);
    holly_init(bus->holly, 0x800000);
}

#define MAP_READ(s, l, h, d) \
    if ((addr >= (l)) && (addr <= (h))) return d ## _read ## s (bus->d, addr - l)

#define MAP_WRITE(s, l, h, d) \
    if ((addr >= (l)) && (addr <= (h))) { d ## _write ## s (bus->d, addr - l, data); return; }

uint32_t dc_bus_read8(dc_bus_state* bus, uint32_t addr) {
    uint32_t raddr = addr;

    addr &= 0x1fffffff;

    MAP_READ(8, 0x04000000, 0x07FFFFFF, holly);
    MAP_READ(8, 0x0C000000, 0x0FFFFFFF, ram);

    printf("unhandled 8-bit read addr=%08x (%08x)\n", raddr, addr);

    return 0xcccccccc;
}

uint32_t dc_bus_read16(dc_bus_state* bus, uint32_t addr) {
    uint32_t raddr = addr;

    addr &= 0x1fffffff;

    MAP_READ(16, 0x04000000, 0x07FFFFFF, holly);
    MAP_READ(16, 0x0C000000, 0x0FFFFFFF, ram);

    printf("unhandled 16-bit read addr=%08x (%08x)\n", raddr, addr);

    return 0xcccccccc;
}

uint32_t dc_bus_read32(dc_bus_state* bus, uint32_t addr) {
    uint32_t raddr = addr;

    addr &= 0x1fffffff;

    MAP_READ(32, 0x04000000, 0x07FFFFFF, holly);
    MAP_READ(32, 0x0C000000, 0x0FFFFFFF, ram);

    printf("unhandled 32-bit read addr=%08x (%08x)\n", raddr, addr);

    return 0xcccccccc;
}

void dc_bus_write8(dc_bus_state* bus, uint32_t addr, uint32_t data) {
    uint32_t raddr = addr;

    addr &= 0x1fffffff;

    MAP_WRITE(8, 0x04000000, 0x07FFFFFF, holly);
    MAP_WRITE(8, 0x0C000000, 0x0FFFFFFF, ram);

    printf("unhandled 8-bit write addr=%08x (%08x) data=%02x\n", raddr, addr, data);
}

void dc_bus_write16(dc_bus_state* bus, uint32_t addr, uint32_t data) {
    uint32_t raddr = addr;

    addr &= 0x1fffffff;

    MAP_WRITE(16, 0x04000000, 0x07FFFFFF, holly);
    MAP_WRITE(16, 0x0C000000, 0x0FFFFFFF, ram);

    printf("unhandled 16-bit write addr=%08x (%08x) data=%04x\n", raddr, addr, data);
}

void dc_bus_write32(dc_bus_state* bus, uint32_t addr, uint32_t data) {
    uint32_t raddr = addr;

    addr &= 0x1fffffff;

    MAP_WRITE(32, 0x04000000, 0x07FFFFFF, holly);
    MAP_WRITE(32, 0x0C000000, 0x0FFFFFFF, ram);

    printf("unhandled 32-bit write addr=%08x (%08x) data=%08x\n", raddr, addr, data);
}

#undef MAP_READ
#undef MAP_WRITE

void dc_bus_destroy(dc_bus_state* bus) {
    ram_destroy(bus->ram);
    free(bus);
}