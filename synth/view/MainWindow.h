//
// Created by schel.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SDL3/SDL.h>
class MainWindow {
    public :
        void init();
    void run();
private:
    void draw();
    SDL_Window* window { nullptr };
    SDL_Renderer* renderer { nullptr };
};

#endif //MAINWINDOW_H
