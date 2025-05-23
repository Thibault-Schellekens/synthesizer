//
// Created by schel.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <map>
#include <SDL3/SDL.h>

#include "../model/Parameters.h"
#include "../model/ParametersManager.h"

class MainWindow {
public :
    MainWindow(ParametersManager& parametersManager);
    void init();
    void run();

private:
    void draw();
    void initKeyMap();
    void processKey(const SDL_KeyboardEvent &event, bool keyDown);

    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};

    ParametersManager& _parametersManager;
    Parameters _parameters;

    std::map<SDL_Keycode, int> _keyMap;


};

#endif //MAINWINDOW_H
