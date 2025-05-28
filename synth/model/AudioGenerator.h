//
// Created by schel.
//

#ifndef AUDIOGENERATOR_H
#define AUDIOGENERATOR_H

#include "AudioBuffer.h"
#include "Enveloppe.h"
#include "Filter.h"
#include "Oscillator.h"
#include "ParametersManager.h"
#include "portaudio.h"

class AudioGenerator {
public:
    AudioGenerator(ParametersManager& parametersManager);
    void init();

private:
    static int audioCallback( const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData );
    void generateAudio(float* outputBuffer, unsigned long framesPerBuffer);
    void updateParameters();

    double currentTimeInSeconds {0.0};

    ParametersManager& _parametersManager;

    AudioBuffer _audioBuffer;
    Oscillator _oscillator1;
    Oscillator _oscillator2;
    Enveloppe _enveloppe;
    Filter _filter;



};

#endif //AUDIOGENERATOR_H
