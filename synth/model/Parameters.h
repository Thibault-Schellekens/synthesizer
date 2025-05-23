//
// Created by schel.
//

#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <optional>

enum class Waveform {
    SINE, SQUARE, SAW
};

struct Parameters {
    bool osc1Enabled {true};
    Waveform osc1Waveform {Waveform::SINE};
    float osc1FrequencyOffset {0.0f};
    bool osc2Enabled {true};
    float attackTime {0.0f};
    float releaseTime {0.0f};
    float filterCutoff {20000.0f};
    float filterResonance {0.0f};
    float delayTime {0.1f};
    float delayMix {0.0f};

    std::optional<int> note;

};

#endif //PARAMETERS_H
