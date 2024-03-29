#include <stdint.h>

#include "sh4.h"
#include "sh4_p4.h"
#include "sh4_cache.h"

// For some reason, the OC on RAM mode only accepts U0/P0 accesses
// on the 4th mirror (60000000-7fffffff).
// This is weird and it breaks my design pretty badly, the operand
// cache is basically unmirrored, contrary to the rest of the
// memory map.

uint32_t sh4_ibus_read8(sh4_state* cpu, uint32_t addr) {
    if (addr >= 0x7c000000 && addr <= 0x7fffffff)
        return cache_read8(cpu->cache, (addr & 0x1fffffff) - 0x7c000000);

    return p4_read8(cpu->p4, addr & 0xffffff);
}

uint32_t sh4_ibus_read16(sh4_state* cpu, uint32_t addr) {
    if (addr >= 0x7c000000 && addr <= 0x7fffffff)
        return cache_read16(cpu->cache, (addr & 0x1fffffff) - 0x7c000000);

    return p4_read16(cpu->p4, addr & 0xffffff);
}

uint32_t sh4_ibus_read32(sh4_state* cpu, uint32_t addr) {
    if (addr >= 0x7c000000 && addr <= 0x7fffffff)
        return cache_read32(cpu->cache, (addr & 0x1fffffff) - 0x7c000000);

    return p4_read32(cpu->p4, addr & 0xffffff);
}

void sh4_ibus_write8(sh4_state* cpu, uint32_t addr, uint32_t data) {
    if (addr >= 0x7c000000 && addr <= 0x7fffffff)
        { cache_write8(cpu->cache, (addr & 0x1fffffff) - 0x7c000000, data); return; }

    p4_write8(cpu->p4, addr & 0xffffff, data);
}

void sh4_ibus_write16(sh4_state* cpu, uint32_t addr, uint32_t data) {
    if (addr >= 0x7c000000 && addr <= 0x7fffffff)
        { cache_write16(cpu->cache, (addr & 0x1fffffff) - 0x7c000000, data); return; }

    p4_write16(cpu->p4, addr & 0xffffff, data);
}

void sh4_ibus_write32(sh4_state* cpu, uint32_t addr, uint32_t data) {
    if (addr >= 0x7c000000 && addr <= 0x7fffffff)
        { cache_write32(cpu->cache, (addr & 0x1fffffff) - 0x7c000000, data); return; }

    p4_write32(cpu->p4, addr & 0xffffff, data);
}
