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
    bus->cache = cache_create();
    bus->vram = vram_create();
    bus->p4 = p4_create();
    bus->ram = ram_create();
    bus->pvr2 = pvr2_create();

    cache_init(bus->cache, bus->p4);
    vram_init(bus->vram, 0x800000);
    p4_init(bus->p4);
    ram_init(bus->ram, 0x1000000);
    pvr2_init(bus->pvr2, bus->vram);
}

#define MAP_READ(s, l, h, d) \
    if ((addr >= (l)) && (addr <= (h))) return d ## _read ## s (bus->d, addr - l)

#define MAP_WRITE(s, l, h, d) \
    if ((addr >= (l)) && (addr <= (h))) { d ## _write ## s (bus->d, addr - l, data); return; }

#define MAP_READ_U(s, l, h, d) \
    if ((uaddr >= (l)) && (uaddr <= (h))) return d ## _read ## s (bus->d, addr - l)

#define MAP_WRITE_U(s, l, h, d) \
    if ((uaddr >= (l)) && (uaddr <= (h))) { d ## _write ## s (bus->d, addr - l, data); return; }

uint32_t dc_bus_read8(dc_bus_state* bus, uint32_t addr) {
    uint32_t uaddr = addr;

    addr &= 0x1fffffff;

    MAP_READ_U(8, 0x1C000000, 0x7FFFFFFF, cache);
    MAP_READ(8, 0x005F8000, 0x005F8FFF, pvr2);
    MAP_READ(8, 0x04000000, 0x07FFFFFF, vram);
    MAP_READ(8, 0x0C000000, 0x0FFFFFFF, ram);
    MAP_READ(8, 0x1F000000, 0x1FFFFFFF, p4);

    printf("unhandled 8-bit read addr=%08x (%08x)\n", uaddr, addr);

    return 0x00000000;
}

uint32_t dc_bus_read16(dc_bus_state* bus, uint32_t addr) {
    uint32_t uaddr = addr;

    addr &= 0x1fffffff;

    MAP_READ_U(16, 0x1C000000, 0x7FFFFFFF, cache);
    MAP_READ(32, 0x005F8000, 0x005F8FFF, pvr2);
    MAP_READ(16, 0x04000000, 0x07FFFFFF, vram);
    MAP_READ(16, 0x0C000000, 0x0FFFFFFF, ram);
    MAP_READ(16, 0x1F000000, 0x1FFFFFFF, p4);

    printf("unhandled 16-bit read addr=%08x (%08x)\n", uaddr, addr);

    return 0x00000000;
}

uint32_t dc_bus_read32(dc_bus_state* bus, uint32_t addr) {
    uint32_t uaddr = addr;

    addr &= 0x1fffffff;

    MAP_READ_U(32, 0x1C000000, 0x7FFFFFFF, cache);
    MAP_READ(32, 0x005F8000, 0x005F8FFF, pvr2);
    MAP_READ(32, 0x04000000, 0x07FFFFFF, vram);
    MAP_READ(32, 0x0C000000, 0x0FFFFFFF, ram);
    MAP_READ(32, 0x1F000000, 0x1FFFFFFF, p4);

    // printf("unhandled 32-bit read addr=%08x (%08x)\n", uaddr, addr);

    return 0x00000000;
}

void dc_bus_write8(dc_bus_state* bus, uint32_t addr, uint32_t data) {
    uint32_t uaddr = addr;

    addr &= 0x1fffffff;

    MAP_WRITE_U(8, 0x1C000000, 0x7FFFFFFF, cache);
    MAP_WRITE(8, 0x005F8000, 0x005F8FFF, pvr2);
    MAP_WRITE(8, 0x04000000, 0x07FFFFFF, vram);
    MAP_WRITE(8, 0x0C000000, 0x0FFFFFFF, ram);
    MAP_WRITE(8, 0x1F000000, 0x1FFFFFFF, p4);

    printf("unhandled 8-bit write addr=%08x (%08x) data=%02x\n", uaddr, addr, data);
}

void dc_bus_write16(dc_bus_state* bus, uint32_t addr, uint32_t data) {
    uint32_t uaddr = addr;

    addr &= 0x1fffffff;

    MAP_WRITE_U(16, 0x1C000000, 0x7FFFFFFF, cache);
    MAP_WRITE(16, 0x005F8000, 0x005F8FFF, pvr2);
    MAP_WRITE(16, 0x04000000, 0x07FFFFFF, vram);
    MAP_WRITE(16, 0x0C000000, 0x0FFFFFFF, ram);
    MAP_WRITE(16, 0x1F000000, 0x1FFFFFFF, p4);

    printf("unhandled 16-bit write addr=%08x (%08x) data=%04x\n", uaddr, addr, data);
}

void dc_bus_write32(dc_bus_state* bus, uint32_t addr, uint32_t data) {
    uint32_t uaddr = addr;

    addr &= 0x1fffffff;

    MAP_WRITE_U(32, 0x1C000000, 0x7FFFFFFF, cache);
    MAP_WRITE(32, 0x005F8000, 0x005F8FFF, pvr2);
    MAP_WRITE(32, 0x04000000, 0x07FFFFFF, vram);
    MAP_WRITE(32, 0x0C000000, 0x0FFFFFFF, ram);
    MAP_WRITE(32, 0x1F000000, 0x1FFFFFFF, p4);

    // printf("unhandled 32-bit write addr=%08x (%08x) data=%08x\n", uaddr, addr, data);
}

#undef MAP_READ
#undef MAP_WRITE
#undef MAP_READ_U
#undef MAP_WRITE_U

void dc_bus_destroy(dc_bus_state* bus) {
    ram_destroy(bus->ram);
    free(bus);
}