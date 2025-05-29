//
// Created by schel.
//

#include "Filter.h"
#include <cmath>
#include <bits/stl_algo.h>

#include "constants.h"

Filter::Filter() {
    updateInternParameters();
}

void Filter::processAudioBuffer(AudioBuffer &audioBuffer) {
    for (unsigned frame = 0; frame < Constants::FRAMES_PER_BUFFER; ++frame) {
        float input = audioBuffer.buffer[frame];

        float output = a0 * input + a1 * x1 + a2 * x2 - b1 * y1 - b2 * y2;

        x2 = x1;
        x1 = input;
        y2 = y1;
        y1 = output;

        audioBuffer.buffer[frame] = output;
    }
}

void Filter::setCutOff(float cutoff) {
    _cutoff = cutoff;
    updateInternParameters();
}

void Filter::setResonance(float resonance) {
    _resonance = std::clamp(resonance, 0.0f, 0.99f);
    updateInternParameters();
}

void Filter::updateInternParameters() {
    float q = 0.5f / (1.0f - _resonance);
    float omega = 2.0f * M_PI * _cutoff / Constants::SAMPLE_RATE;

    float alpha = sinf(omega) / (2.0f * q);
    float cosw = cosf(omega);

    float norm = 1.0f / (1.0f + alpha);
    a0 = (1.0f - cosw) * 0.5f * norm;
    a1 = (1.0f - cosw) * norm;
    a2 = a0;
    b1 = -2.0f * cosw * norm;
    b2 = (1.0f - alpha) * norm;
}
