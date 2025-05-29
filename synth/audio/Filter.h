//
// Created by schel.
//

#ifndef FILTER_H
#define FILTER_H
#include "AudioBuffer.h"

class Filter {
public:
    Filter();
    void processAudioBuffer(AudioBuffer &audioBuffer);

    void setCutOff(float cutoff);
    void setResonance(float resonance);

private:
    void updateInternParameters();

    float _cutoff{20000.0f};
    float _resonance{0.0f};

    float a0{}, a1{}, a2{}, b0{}, b1{}, b2{};

    float x1{}, x2{}, y1{}, y2{};
};

#endif //FILTER_H
