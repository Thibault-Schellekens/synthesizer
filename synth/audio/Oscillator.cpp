//
// Created by schel.
//

#include "Oscillator.h"
#include <cmath>

#include "constants.h"

Oscillator::Oscillator(Waveform waveform) : _waveform(waveform) {
    setPhaseIncrement();
}

void Oscillator::processAudioBuffer(AudioBuffer &audioBuffer) {
    if (!_enabled) return;

    for (int frame = 0; frame < Constants::FRAMES_PER_BUFFER; ++frame) {
        float sample{0.0f};

        switch (_waveform) {
            case Waveform::SINE:
                sample = cosf(_currentPhase) * 0.5f;
                break;
            case Waveform::SQUARE:
                sample = (_currentPhase < M_PI) ? 0.5f : -0.5f;
                break;
            case Waveform::SAW:
                sample = (_currentPhase / (2.0f * M_PI)) - 0.5f;
                break;
        }

        _currentPhase += _phaseIncrement;
        _currentPhase = fmod(_currentPhase, 2.0f * M_PI);

        audioBuffer.buffer[frame] += sample;
    }
}

void Oscillator::setFrequency(float frequency) {
    _frequency = frequency;
    setPhaseIncrement();
}

void Oscillator::setFrequencyOffset(float offset) {
    _frequencyOffset = offset;
    setPhaseIncrement();
}

void Oscillator::setWaveform(Waveform waveform) {
    _waveform = waveform;
}

void Oscillator::setEnabled(bool enabled) {
    _enabled = enabled;
}

void Oscillator::setPhaseIncrement() {
    _phaseIncrement = 2 * M_PI * (_frequency + _frequencyOffset) / Constants::SAMPLE_RATE;
}
