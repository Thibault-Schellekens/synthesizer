//
// Created by schel.
//

#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include "AudioBuffer.h"
#include "Parameters.h"

class Oscillator {
public:
    explicit Oscillator(Waveform waveform);
    void processAudioBuffer(AudioBuffer& audioBuffer);

    void setFrequency(float frequency);
    void setFrequencyOffset(float offset);
    void setWaveform(Waveform waveform);
    void setEnabled(bool enabled);

private:
    float _currentPhase {0.0f};
    float _phaseIncrement {0.0f};
    float _frequency {0.0f};
    float _frequencyOffset {0.0f};
    Waveform _waveform;
    bool _enabled {false};

    void setPhaseIncrement();

};

#endif //OSCILLATOR_H
