//
// Created by schel.
//

#ifndef PARAMETERSMANAGER_H
#define PARAMETERSMANAGER_H
#include <mutex>

#include "../Parameters.h"

class ParametersManager {
public:
    [[nodiscard]] Parameters getParameters();
    void setParameters(const Parameters &parameters);

private:
    Parameters _parameters;
    std::mutex _mutex;
};

#endif //PARAMETERSMANAGER_H
