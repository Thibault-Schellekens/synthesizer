//
// Created by schel.
//

#include "ParametersManager.h"

Parameters ParametersManager::getParameters() {
    std::lock_guard lock(_mutex);
    return _parameters;
}

void ParametersManager::setParameters(const Parameters &parameters) {
    std::lock_guard lock(_mutex);
    _parameters = parameters;
}
