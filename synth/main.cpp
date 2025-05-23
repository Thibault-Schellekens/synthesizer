#include <iostream>

#include "model/AudioGenerator.h"
#include "view/MainWindow.h"

int main() {
    AudioGenerator audioGenerator;
    audioGenerator.init();

    MainWindow mainWindow;
    mainWindow.init();
    mainWindow.run();


    return 0;
}
