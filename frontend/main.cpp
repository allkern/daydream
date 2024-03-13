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
#include <SDL_syswm.h>
#include <filesystem>
#include <string>
#include <vector>

#include "sh4_dis.h"
#include "sh4.h"
#include "bus.h"

#include "IconsMaterialDesign.h"

#include <dwmapi.h>

std::vector <std::filesystem::path> game_paths;

void scan_games(const char* path) {
    for (const auto& p : std::filesystem::directory_iterator(path))
        if (p.is_directory())
            game_paths.push_back(p);
}

namespace ImGui {
    void VerticalSeparator(float thickness = 1.0f) {
        ImVec4 separator_color = ImGui::GetStyle().Colors[ImGuiCol_Separator];

        ImDrawList* draw = ImGui::GetWindowDrawList();

        ImGui::SameLine();

        ImVec2 p = ImGui::GetCursorScreenPos();

        draw->AddLine(
            p,
            ImVec2(p.x, p.y + GetContentRegionAvail().y),
            ImGui::GetColorU32(separator_color),
            thickness
        );
    }
}

void load_game(dc_bus_state* bus, const std::filesystem::path& p) {
    std::string game_path = p.string();

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
}

static ImVec4 col_mnemonic = ImVec4((181.0 + 30.0) / 255.0, (137.0 + 30.0) / 255.0, 0.0, 1.0);
static ImVec4 col_invalid = ImVec4(0.35, 0.35, 0.35, 1.0);

void highlight_asm(sh4_state* cpu, bool print_address = true, bool print_opcode = true) {
    using namespace ImGui;

    sh4d_state dis_state;

    dis_state.print_address = (print_address == true) ? 1 : 0;
    dis_state.print_opcode = (print_opcode == true) ? 1 : 0;

    char buf[128];

    int count = 24;
    int offset = count / 2;

    ImDrawList* draw = ImGui::GetWindowDrawList();

    float width = GetContentRegionAvail().x;
    float height = GetTextLineHeight();

    for (int i = 0; i < count; i++) {
        ImVec2 p = GetCursorScreenPos();

        if (i == offset)
            draw->AddRectFilled(p, ImVec2(p.x + width, p.y + height), 0x7f303030, 4.0); // ABGR

        if (dis_state.pc == 0xa0000010)
            draw->AddRectFilled(p, ImVec2(p.x + width, p.y + height), 0x7f00007f, 4.0);

        if (dis_state.pc == 0xa0000014)
            draw->AddRectFilled(p, ImVec2(p.x + width, p.y + height), 0x7f00007f, 4.0);

        if (dis_state.pc == 0xa000001e)
            draw->AddRectFilled(p, ImVec2(p.x + width, p.y + height), 0x7f00007f, 4.0);

        dis_state.pc = cpu->pc[0] + (i << 1) - (offset << 1);

        uint16_t opcode = cpu->bus.read16(cpu->bus.udata, dis_state.pc);

        std::string str = sh4_disassemble(opcode, buf, &dis_state);

        if (dis_state.print_address) {
            auto p = str.find_first_of(':');

            std::string address = str.substr(0, p);

            str = str.substr(p + 2);

            TextColored(ImVec4(0.75, 0.75, 0.75, 1.0), "%s ", address.c_str());

            float y0 = GetCursorScreenPos().y;

            SameLine(0.0, 4.0);

            float x = GetCursorScreenPos().x;
            float y1 = GetCursorScreenPos().y;
        }

        if (dis_state.print_opcode) {
            auto p = str.find_first_of(' ');

            std::string opcode = str.substr(0, p);

            str = str.substr(p + 1);

            TextColored(ImVec4(0.5, 0.5, 0.5, 1.0), "%s ", opcode.c_str());

            SameLine(0.0, 5.0);
        }

        {
            auto p = str.find_first_of(' ');

            std::string opcode = str.substr(0, p);

            str = (p == std::string::npos) ? "" : str.substr(p + 1);

            TextColored(opcode == "<invalid>" ? col_invalid : col_mnemonic, "%s", opcode.c_str());

            SameLine();

            Text(str.c_str());
        }
    }
}

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

    printf("Scanning games directory... ");

    scan_games(".\\roms\\");

    printf("done\n");

    // To-do: Move this platform-specific code somewhere else, ASAP!
    //        Research minimum supported version for dwAttribute 20

    // Set window dark mode and remove icon (Windows-specific)
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND hwnd = wmInfo.info.win.window;

    COLORREF color = 0x00000001;

    DwmSetWindowAttribute(hwnd, 20, &color, sizeof(COLORREF));

    // End platform-specific

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
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha            = 1.0f;
    style.WindowBorderSize = 0.0f;
    style.WindowRounding   = 8.0f;
    style.FrameBorderSize  = 0.0f;
    style.FrameRounding    = 4.0f;
    style.ChildBorderSize  = 0.0f;
    style.PopupBorderSize  = 0.0f;
    style.PopupRounding    = 4.0f;
    style.FramePadding     = ImVec2(6.0, 6.0);
    style.Colors[ImGuiCol_Button]        = ImVec4(0.35, 0.35, 0.35, 1.0);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.40, 0.40, 0.40, 1.0);
    style.Colors[ImGuiCol_ButtonActive]  = ImVec4(0.45, 0.45, 0.45, 1.0);
    style.Colors[ImGuiCol_WindowBg]      = ImVec4(0.10, 0.10, 0.10, 0.95);
    style.Colors[ImGuiCol_FrameBg]       = ImVec4(0.35, 0.35, 0.35, 1.0);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.22, 0.22, 0.22, 1.0);
    style.Colors[ImGuiCol_Header]        = ImVec4(0.28, 0.28, 0.28, 1.0);
    // style.Colors[ImGuiCol_WindowBg]      = ImVec4(0.17, 0.17, 0.17, 1.0);
    // style.Colors[ImGuiCol_Button]        = ImVec4(0.17, 0.17, 0.17, 1.0);
    // style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.22, 0.22, 0.22, 1.0);
    // style.Colors[ImGuiCol_ButtonActive]  = ImVec4(0.28, 0.28, 0.28, 1.0);

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    io.Fonts->AddFontDefault();

    static const ImWchar ranges[] = { ICON_MIN_MD, ICON_MAX_16_MD, 0 };
    ImFont* small   = io.Fonts->AddFontFromFileTTF("Roboto-Regular.ttf", 11.0f);
    ImFont* body    = io.Fonts->AddFontFromFileTTF("Roboto-Regular.ttf", 14.0f);
    ImFont* code    = io.Fonts->AddFontFromFileTTF("RobotoMono-Regular.ttf", 18.0f);
    ImFont* heading = io.Fonts->AddFontFromFileTTF("Roboto-Regular.ttf", 18.0f);
    ImFont* icons   = io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_MD, 18.0f, nullptr, ranges);

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
    bool sh4_enabled = false;
    bool print_address = true;
    bool print_opcode = true;
    bool show_gamelist = true;
    float menubar_height = 0;

    while (open) {
        using namespace ImGui;

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        NewFrame();

        PushFont(body);

        if (BeginMainMenuBar()) {
            menubar_height = GetWindowHeight();

            if (BeginMenu("Dreamcast")) {
                if (MenuItem("Start BIOS")) {
                    if (!sh4_enabled)
                        run = true;

                    show_gamelist = false;
                }
                
                if (MenuItem("Start IP.BIN")) {
                    sh4_set_pc(cpu, 0xac008300);

                    if (!sh4_enabled)
                        run = true;

                    show_gamelist = false;
                }

                if (MenuItem("Start 1ST_READ.BIN")) {
                    sh4_set_pc(cpu, 0xac010000);

                    if (!sh4_enabled)
                        run = true;

                    show_gamelist = false;
                }

                if (MenuItem(show_gamelist ? "Hide game list" : "Show game list")) {
                    run = false;
                    show_gamelist = !show_gamelist;
                }

                if (MenuItem(run ? "Pause" : "Resume"))
                    run = !run;

                ImGui::EndMenu();
            }

            if (BeginMenu("Display")) {
                if (MenuItem(bilinear ? "Nearest Neighbor" : "Bilinear")) {
                    bilinear = !bilinear;

                    SDL_SetTextureScaleMode(texture, (SDL_ScaleMode)bilinear);
                }

                ImGui::EndMenu();
            }

            if (BeginMenu("Debug")) {
                if (MenuItem(sh4_enabled ? "Hide SH4 debugger" : "Show SH4 debugger")) {
                    sh4_enabled = !sh4_enabled;
                }

                ImGui::EndMenu();
            }

            EndMainMenuBar();
        }

        if (show_gamelist) {
            PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0);

            SetNextWindowPos(ImVec2(0, menubar_height));
            SetNextWindowSize(ImVec2(640*1.5, 480*1.5-menubar_height));
            if (Begin("gamelist", nullptr,
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoDecoration
            )) {
                if (BeginTable("gamelist#table", 3, ImGuiTableFlags_RowBg)) {
                    for (const auto& p : game_paths) {
                        TableNextRow();

                        TableSetColumnIndex(0);

                        if (Selectable(p.stem().string().c_str(), false, ImGuiSelectableFlags_SpanAllColumns)) {
                            load_game(bus, p);
                        }

                        TableNextColumn();

                        Text("CUE");

                        TableNextColumn();

                        Text("Game");
                    }

                    EndTable();
                }
            } End();

            PopStyleVar();
        }

        if (sh4_enabled) {
            SetNextWindowSize(ImVec2(700, 580));
            if (Begin("SH4", nullptr,
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoDecoration
            )) {
                BeginChild("##codeviewmain", ImVec2(350, 0));
                PushFont(icons);

                if (Button(run ? ICON_MD_PAUSE : ICON_MD_PLAY_ARROW, ImVec2(GetContentRegionAvail().x / 8.0, 0.0)))
                    run = !run;

                SameLine();

                BeginDisabled(run);

                if (Button(ICON_MD_ARROW_FORWARD))
                    sh4_cycle(cpu);

                EndDisabled();

                // VerticalSeparator();

                SameLine();

                if (Button(ICON_MD_APP_SETTINGS_ALT))
                    OpenPopup("codeview##settings");

                PushFont(body);

                if (BeginPopup("codeview##settings")) {
                    ImGui::MenuItem("Show address", "", &print_address);
                    ImGui::MenuItem("Show opcode", "", &print_opcode);

                    EndPopup();
                }

                PopFont();

                PopFont();

                PushFont(code);
                BeginChild("codeview");

                highlight_asm(cpu, print_address, print_opcode);

                EndChild();
                PopFont();
                EndChild(); SameLine();

                BeginChild("registers");

                PushFont(code);

                for (int y = 0; y < 4; y++) {
                    for (int x = 0; x < 4; x++) {
                        int i = x + (y * 4);

                        Text("%08x", *sh4_get_reg(cpu, i));

                        SameLine();
                    }

                    NewLine();
                }

                PopFont();

                EndChild();
            } End();
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
        }

        void* display = pvr2_get_display(bus->pvr2);

        SDL_UpdateTexture(texture, NULL, display, 640 * 4);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

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
