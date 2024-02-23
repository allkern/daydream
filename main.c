#include <stdio.h>

#include "sh4_dis.h"
#include "sh4.h"
#include "bus.h"

#include "SDL2/SDL.h"

#undef main

int main(int argc, const char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window* window = SDL_CreateWindow(
        "daydream",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1280, 960,
        SDL_WINDOW_OPENGL
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        640, 480
    );

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

    int len = strlen(argv[1]);

    if (!strnicmp(argv[1], "-g", len)) {
        printf("Loading \'%s\' at 0x8c008000...\n", argv[2]);

        // Load IP.BIN at 0x8c008000
        ram_load(bus->ram, argv[2], 0x8000);

        // Load 1ST_READ.BIN at 0x8c010000
        ram_load(bus->ram, "1ST_READ.BIN", 0x10000);

        sh4_set_reg(cpu, 15, 0x8c00d400);
        sh4_set_pc(cpu, 0xac008300);
    } else {
        printf("Loading \'%s\' at 0x8c001000\n", argv[1]);

        // Load test program at 0x8c001000
        ram_load(bus->ram, argv[1], 0x1000);

        sh4_set_pc(cpu, 0xac001000);
    }

    int open = 1;

    while (open) {
        int counter = 750000;

        while (counter--)
            sh4_cycle(cpu);

        void* display = pvr2_get_display(bus->pvr2);

        SDL_UpdateTexture(texture, NULL, display, 640 * 4);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    open = 0;
                } break;
            }
        }
    }

    putchar('\n');

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            printf("R%-2u: %08x ", x + (y * 4), *sh4_get_reg(cpu, x + (y * 4)));
        }

        putchar('\n');
    }

    sh4_destroy(cpu);
}