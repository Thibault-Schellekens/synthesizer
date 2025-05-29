//
// Created by schel.
//

#ifndef ENVELOPPE_H
#define ENVELOPPE_H
#include "AudioBuffer.h"

enum class Stage {
    ATTACK,
    SUSTAIN,
    RELEASE,
    OFF
};

class Envelope {
public:
    void processAudioBuffer(AudioBuffer& audioBuffer);
    void noteOn();
    void noteOff();

    void setAttackTime(float attack);
    void setReleaseTime(float release);

private:
    void updateAmplitude();

    float _attackTime {0.5f};
    float _releaseTime {1.0f};
    float _amplitude {0.0f};
    Stage _stage {Stage::OFF};

};

#endif //ENVELOPPE_H
