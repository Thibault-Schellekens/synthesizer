//
// Created by schel.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SDL3/SDL.h>

#include "../model/Parameters.h"

class MainWindow {
    public :
        void init();
    void run();
private:
    void draw();
    SDL_Window* window { nullptr };
    SDL_Renderer* renderer { nullptr };

    Parameters _parameters;
};

#endif //MAINWINDOW_H
