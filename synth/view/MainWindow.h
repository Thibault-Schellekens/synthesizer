//
// Created by schel.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <map>
#include <SDL3/SDL.h>

#include "../model/Parameters.h"

class MainWindow {
public :
    MainWindow();
    void init();
    void run();

private:
    void draw();
    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};

    Parameters _parameters;

    std::map<SDL_Keycode, int> _keyMap;

    void initKeyMap();
    void processKey(const SDL_KeyboardEvent &event, bool keyDown);
};

#endif //MAINWINDOW_H
