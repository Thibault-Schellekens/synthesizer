//
// Created by schel.
//

#include <iostream>
#include <cmath>
#include "AudioGenerator.h"

#include "constants.h"

AudioGenerator::AudioGenerator(ParametersManager &parametersManager)
: _parametersManager(parametersManager),
  _audioBuffer(AudioBuffer(Constants::FRAMES_PER_BUFFER)),
  _oscillator1(Oscillator(Waveform::SINE)),
  _oscillator2(Oscillator(Waveform::SAW)) {
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

void AudioGenerator::generateAudio(float *outputBuffer, unsigned long framesPerBuffer) {
    updateParameters();

    std::fill(_audioBuffer.buffer.begin(), _audioBuffer.buffer.end(), 0.0f);

    _oscillator1.processAudioBuffer(_audioBuffer);
    _oscillator2.processAudioBuffer(_audioBuffer);

    for (unsigned long i = 0; i < framesPerBuffer; ++i) {
        *outputBuffer++ = _audioBuffer.buffer[i]; // canal gauche
        *outputBuffer++ = _audioBuffer.buffer[i]; // canal droit
    }
}

void AudioGenerator::updateParameters() {
    Parameters parameters = _parametersManager.getParameters();

    _oscillator1.setEnabled(parameters.osc1Enabled);
    _oscillator1.setWaveform(parameters.osc1Waveform);
    _oscillator1.setFrequencyOffset(parameters.osc1FrequencyOffset);

    _oscillator2.setEnabled(parameters.osc2Enabled);

    if (parameters.note.has_value()) {
        const float frequency = 220.0f * std::pow(2, (parameters.note.value() - 1) / 12.0);
        _oscillator1.setFrequency(frequency);
        _oscillator2.setFrequency(frequency);
    }
}
