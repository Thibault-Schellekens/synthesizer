//
// Created by schel.
//


#include "MainWindow.h"
#include <thread>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

constexpr float FRAMERATE = 60.0f;
constexpr std::chrono::duration<double, std::milli> TARGET_FRAMETIME(1000.0 / FRAMERATE);

MainWindow::MainWindow(ParametersManager &parametersManager) : _parametersManager(parametersManager) {
    initKeyMap();
}

void MainWindow::initKeyMap() {
    _keyMap = {
        {SDLK_Q, 1},
        {SDLK_Z, 2},
        {SDLK_S, 3},
        {SDLK_E, 4},
        {SDLK_D, 5},
        {SDLK_F, 6},
        {SDLK_T, 7},
        {SDLK_G, 8},
        {SDLK_Y, 9},
        {SDLK_H, 10},
        {SDLK_U, 11},
        {SDLK_J, 12},
    };
}


void MainWindow::init() {
    // Setup SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        SDL_Log("Error: SDL_Init(): %s\n", SDL_GetError());
        return;
    }
    // Create window with SDL_Renderer graphics context
    Uint32 window_flags = SDL_WINDOW_HIDDEN;
    window = SDL_CreateWindow("", 800, 600, window_flags);
    if (nullptr == window) {
        SDL_Log("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return;
    }
    renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);
    if (nullptr == renderer) {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return;
    }
    SDL_SetWindowPosition(
        window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup DearImGui style
    ImGui::StyleColorsLight();
    ImGui::GetStyle().WindowRounding = 0.0f;
    ImGui::GetStyle().WindowMinSize = ImVec2(800, 600);

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void MainWindow::run() {
    const auto clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool done{false};
    while (!done) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (SDL_EVENT_QUIT == event.type)
                done = true;
            if ((SDL_EVENT_WINDOW_CLOSE_REQUESTED == event.type)
                && (SDL_GetWindowID(window) == event.window.windowID))
                done = true;
            else if (event.type == SDL_EVENT_KEY_DOWN)
                processKey(event.key, true);
            else if (event.type == SDL_EVENT_KEY_UP)
                processKey(event.key, false);
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // all the UI code description
        draw();

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColorFloat(renderer,
                                    clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);

        // Calculate time spent and sleep if needed
        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto frameDuration = frameEnd - frameStart;
        if (frameDuration < TARGET_FRAMETIME) {
            std::this_thread::sleep_for(TARGET_FRAMETIME - frameDuration);
        }
    }

    // Cleanup
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void MainWindow::draw() {
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
    ImGui::Begin("Synthesizer", nullptr, window_flags);

    ImGui::Checkbox("Oscillator 1", &_parameters.osc1Enabled);
    ImGui::SameLine(150.0);
    ImGui::Checkbox("Oscillator 2", &_parameters.osc2Enabled);

    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    int waveform = static_cast<int>(_parameters.osc1Waveform);
    if (ImGui::Combo("OSC1 Waveform", &waveform, "Sine\0Square\0Saw\0")) {
        _parameters.osc1Waveform = static_cast<Waveform>(waveform);
    }
    ImGui::SliderFloat("Freq Offset OSC1", &_parameters.osc1FrequencyOffset, -5.0f, 5.0f, "%.2f Hz");

    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    ImGui::SliderFloat("Attack", &_parameters.attackTime, 0.0f, 1.0f, "%.2f s");
    ImGui::SliderFloat("Release", &_parameters.releaseTime, 0.0f, 2.0f, "%.2f s");

    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    ImGui::SliderFloat("Filter Cutoff", &_parameters.filterCutoff, 20.0f, 20000.0f, "%.0f Hz");
    ImGui::SliderFloat("Filter Resonance", &_parameters.filterResonance, 0.0f, 1.0f, "%.2f");

    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    ImGui::SliderFloat("Delay Time", &_parameters.delayTime, 0.1f, 2.0f, "%.2f s");
    ImGui::SliderFloat("Delay Mix", &_parameters.delayMix, 0.0f, 1.0f, "%.2f");

    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    ImGui::NewLine();

    for (int i = 1; i <= 12; ++i) {
        ImGui::SameLine();

        bool isSelected = _parameters.note.has_value() && _parameters.note.value() == i;
        if (isSelected) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 1.0f, 1.0f));
        }

        ImGui::Button(std::to_string(i).c_str());

        if (isSelected) {
            ImGui::PopStyleColor(1);
        }

        if (ImGui::IsItemActive()) {
            _parameters.note = i;
        }

        if (ImGui::IsItemDeactivated()) {
            _parameters.note.reset();
        }
    }

    _parametersManager.setParameters(_parameters);

    ImGui::End();
}

void MainWindow::processKey(const SDL_KeyboardEvent &event, const bool keyDown) {
    auto it = _keyMap.find(event.key);

    if (it != _keyMap.end()) {
        int note = it->second;
        if (keyDown) {
            _parameters.note = note;
        } else {
            _parameters.note.reset();
        }
    }
}
