//
// Created by schel.
//

#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include "portaudio.h"

class AudioGenerator {
public:
    void init();

private:
    static int audioCallback( const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData );

    double currentTimeInSeconds {0.0};

};

#endif //AUDIOGENERATOR_H
