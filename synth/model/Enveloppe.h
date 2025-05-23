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

class Enveloppe {
public:
    void processAudioBuffer(AudioBuffer& audioBuffer, double currentTime);
    void noteOn(double currentTime);
    void noteOff(double currentTime);

    void setAttackTime(float attack);
    void setReleaseTime(float release);

private:
    float _attackTime {0.5f};
    float _releaseTime {1.0f};
    float _amplitude {0.0f};
    Stage _stage {Stage::OFF};

    double _triggerOnTime {0.0};
    double _triggerOffTime {0.0};

    void updateAmplitude();
    void updateStage(double time);

};

#endif //ENVELOPPE_H
