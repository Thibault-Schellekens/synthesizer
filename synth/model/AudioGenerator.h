//
// Created by schel.
//

#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include "AudioBuffer.h"
#include "portaudio.h"

class AudioGenerator {
public:
    AudioGenerator();
    void init();

private:
    static int audioCallback( const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData );
    void generateAudio(float* outputBuffer, unsigned long framesPerBuffer);

    double currentTimeInSeconds {0.0};

    AudioBuffer _audioBuffer;



};

#endif //AUDIOGENERATOR_H
