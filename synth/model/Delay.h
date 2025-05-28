//
// Created by schel.
//

#ifndef DELAY_H
#define DELAY_H
#include "AudioBuffer.h"
#include "constants.h"

class Delay {
public:
    Delay();
    void processAudioBuffer(AudioBuffer &audioBuffer);

    void setDelayTime(float delayTime);
    void setDelayMix(float delayMix);

private:
    void updateIndex();

    float _delayTime {0.1f}; // in seconds
    float _delayMix {0.0f};
    unsigned _writeIndex {0};
    unsigned _readIndex {0};

    AudioBuffer _delayBuffer {AudioBuffer(Constants::SAMPLE_RATE * 2)};


};

#endif //DELAY_H
