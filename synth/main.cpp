#include <iostream>

#include "model/AudioGenerator.h"
#include "model/ParametersManager.h"
#include "view/MainWindow.h"

int main() {
    ParametersManager parametersManager;

    AudioGenerator audioGenerator(parametersManager);
    audioGenerator.init();

    MainWindow mainWindow(parametersManager);
    mainWindow.init();
    mainWindow.run();


    return 0;
}
