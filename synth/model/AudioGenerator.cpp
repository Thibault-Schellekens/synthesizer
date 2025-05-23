//
// Created by schel.
//

#include <iostream>
#include "AudioGenerator.h"

#include "constants.h"

AudioGenerator::AudioGenerator()
: _audioBuffer(Constants::FRAMES_PER_BUFFER) {
}

void AudioGenerator::init() {
    PaError errorInit = Pa_Initialize();
    if (errorInit != paNoError) {
        std::cerr << "PortAudio error in Pa_Initialize(): "
                << Pa_GetErrorText(errorInit) << std::endl;
        return;
    }

    PaError errorStream;
    PaStream *stream;

    errorStream = Pa_OpenDefaultStream(&stream,
                                       0,
                                       2,
                                       paFloat32,
                                       Constants::SAMPLE_RATE,
                                       Constants::FRAMES_PER_BUFFER,
                                       audioCallback,
                                       this);

    errorStream = Pa_StartStream(stream);
    if (errorStream != paNoError) {
        std::cerr << "PortAudio error in Pa_StartStream(): "
                << Pa_GetErrorText(errorStream) << std::endl;
    }
}

int AudioGenerator::audioCallback(const void *inputBuffer,
                                  void *outputBuffer,
                                  unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo *timeInfo,
                                  PaStreamCallbackFlags statusFlags,
                                  void *userData) {
    auto *audioGenerator = static_cast<AudioGenerator *>(userData);
    auto *out = static_cast<float *>(outputBuffer);

    audioGenerator->currentTimeInSeconds += framesPerBuffer / Constants::SAMPLE_RATE;

    audioGenerator->generateAudio(out, framesPerBuffer);

    return 0;
}

void AudioGenerator::generateAudio(float* outputBuffer, unsigned long framesPerBuffer) {

    std::fill(_audioBuffer.buffer.begin(), _audioBuffer.buffer.end(), 0.0f);

    for (unsigned long i = 0; i < framesPerBuffer; ++i) {
        *outputBuffer++ = 0.0f; // canal gauche
        *outputBuffer++ = 0.0f; // canal droit
    }
}