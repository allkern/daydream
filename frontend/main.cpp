// Dear ImGui: standalone example application for SDL2 + SDL_Renderer
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

// Important to understand: SDL_Renderer is an _optional_ component of SDL2.
// For a multi-platform app consider using e.g. SDL+DirectX on Windows and SDL+OpenGL on Linux/OSX.

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <string>

#include "sh4.h"
#include "bus.h"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

#define FONT(font, code) { PushFont(font); code; PopFont(); }

#undef main

// Main code
int main(int argc, const char* argv[]) {
    // Setup SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with SDL_Renderer graphics context
    SDL_Window* window = SDL_CreateWindow(
        "Daydream",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640 * 1.5, 480 * 1.5,
        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
    );

    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        640, 480
    );

    SDL_SetTextureScaleMode(texture, SDL_ScaleModeLinear);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    io.Fonts->AddFontDefault();
    ImFont* small   = io.Fonts->AddFontFromFileTTF(".\\Roboto-Regular.ttf", 11.0f);
    ImFont* body    = io.Fonts->AddFontFromFileTTF(".\\Roboto-Regular.ttf", 14.0f);
    ImFont* code    = io.Fonts->AddFontFromFileTTF(".\\RobotoMono-Regular.ttf", 14.0f);
    ImFont* heading = io.Fonts->AddFontFromFileTTF(".\\Roboto-Regular.ttf", 18.0f);

    std::string bios_path = ".\\bios";

    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-b") {
            bios_path = std::string(argv[i+1]);

            break;
        }
    }
    
    if ((bios_path.front() == '\"') ^ (bios_path.back() == '\"')) {
        if (bios_path.front() == '\"') bios_path = bios_path.substr(1);
        if (bios_path.back() == '\"') bios_path.pop_back();
    }

    printf("Searching BIOS and flash files on \'%s\'\n", bios_path.c_str());

    std::string boot_path = bios_path + "\\dc_boot.bin";
    std::string flash_path = bios_path + "\\dc_flash.bin";

    ImGuiStyle& style = ImGui::GetStyle();

    style.FrameBorderSize = 0;
    style.WindowBorderSize = 0;
    
    printf("Initializing Dreamcast with files:\n\tboot: \'%s\'\n\tflash: \'%s\'\n",
        boot_path.c_str(),
        flash_path.c_str()
    );

    dc_bus_state* bus = dc_bus_create();
    dc_bus_init(bus, boot_path.c_str(), flash_path.c_str());

    sh4_bus cpu_bus;

    cpu_bus.udata = bus;
    cpu_bus.read32 = (sh4_bus_read8_func)dc_bus_read32;
    cpu_bus.read16 = (sh4_bus_read16_func)dc_bus_read16;
    cpu_bus.read8 = (sh4_bus_read32_func)dc_bus_read8;
    cpu_bus.write32 = (sh4_bus_write8_func)dc_bus_write32;
    cpu_bus.write16 = (sh4_bus_write16_func)dc_bus_write16;
    cpu_bus.write8 = (sh4_bus_write32_func)dc_bus_write8;

    sh4_state* cpu = sh4_create();
    sh4_init(cpu, cpu_bus);

    std::string game_path;

    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-g") {
            game_path = std::string(argv[i+1]);

            break;
        }
    }

    if ((game_path.front() == '\"') ^ (game_path.back() == '\"')) {
        if (game_path.front() == '\"') game_path = game_path.substr(1);
        if (game_path.back() == '\"') game_path.pop_back();
    }

    printf("Searching files on \'%s\'\n", game_path.c_str());

    std::string ip_path = game_path + "\\IP.BIN";
    std::string read_path = game_path + "\\1ST_READ.BIN";

    printf("Loading \'%s\' at 0x8c008000...\n", ip_path.c_str());

    // Load IP.BIN at 0x8c008000
    ram_load(bus->ram, ip_path.c_str(), 0x8000);

    printf("Loading \'%s\' at 0x8c010000...\n", read_path.c_str());

    // Load 1ST_READ.BIN at 0x8c010000
    ram_load(bus->ram, read_path.c_str(), 0x10000);

    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-x") {
            // To-do: Load executable directly
            printf("Loading \'%s\' at 0x8c001000\n", argv[i+1]);

            // Load test program at 0x8c001000
            ram_load(bus->ram, argv[i+1], 0x1000);

            sh4_set_pc(cpu, 0xac001000);
        }
    }

    // Main loop
    bool open = true;
    bool run = false;
    bool bilinear = true;

    while (open) {
        using namespace ImGui;

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        NewFrame();

        PushFont(body);

        if (BeginMainMenuBar()) {
            if (BeginMenu("Dreamcast")) {
                if (MenuItem("Start BIOS")) {
                    run = true;
                }
                
                if (MenuItem("Start IP.BIN")) {
                    sh4_set_pc(cpu, 0xac008300);

                    run = true;
                }

                if (MenuItem("Start 1ST_READ.BIN")) {
                    sh4_set_pc(cpu, 0xac010000);

                    run = true;
                }

                if (MenuItem(run ? "Pause" : "Resume"))
                    run = !run;

                EndMenu();
            }

            if (BeginMenu("Display")) {
                if (MenuItem(bilinear ? "Nearest Neighbor" : "Bilinear")) {
                    bilinear = !bilinear;

                    SDL_SetTextureScaleMode(texture, (SDL_ScaleMode)bilinear);
                }

                EndMenu();
            }

            if (BeginMenu("Debug")) {
                

                EndMenu();
            }

            EndMainMenuBar();
        }

        PopFont();

        // Rendering
        ImGui::Render();

        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    
        SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0xff);
        SDL_RenderClear(renderer);
    
        if (run) {
            int counter = 750000;

            while (counter--)
                sh4_cycle(cpu);

            void* display = pvr2_get_display(bus->pvr2);

            SDL_UpdateTexture(texture, NULL, display, 640 * 4);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

        SDL_RenderPresent(renderer);

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            switch (event.type) {
                case SDL_QUIT: {
                    open = false;
                } break;
            }
        }
    }

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
