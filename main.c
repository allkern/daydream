#include <stdio.h>

#include "sh4.h"
#include "bus.h"

int main(void) {
    dc_bus_state* bus = dc_bus_create();
    dc_bus_init(bus);

    sh4_bus cpu_bus = {
        .udata   = bus,
        .read32  = dc_bus_read32,
        .read16  = dc_bus_read16,
        .read8   = dc_bus_read8,
        .write32 = dc_bus_write32,
        .write16 = dc_bus_write16,
        .write8  = dc_bus_write8
    };

    sh4_state* cpu = sh4_create();
    sh4_init(cpu, cpu_bus);

    // Load test program at 0x8c001000
    ram_load(bus->ram, "test.bin", 0x1000);

    cpu->pc = 0x8c001000;

    int counter = 16;

    while (counter--)
        sh4_cycle(cpu);

    putchar('\n');

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            printf("R%-2u: %08x ", x + (y * 4), sh4_get_reg(cpu, x + (y * 4)));
        }

        putchar('\n');
    }

    sh4_destroy(cpu);
}