//
// Created by schel.
//

#include "Enveloppe.h"

#include <iostream>
#include <ostream>

#include "constants.h"

void Enveloppe::processAudioBuffer(AudioBuffer &audioBuffer, double currentTime) {
    updateStage(currentTime);

    for (int frame = 0; frame < Constants::FRAMES_PER_BUFFER; ++frame) {
        updateAmplitude();

        audioBuffer.buffer[frame] *= _amplitude;
    }
}

void Enveloppe::noteOn(double currentTime) {
        _stage = Stage::ATTACK;
        _triggerOnTime = currentTime;
}

void Enveloppe::noteOff(double currentTime) {
        _stage = Stage::RELEASE;
        _triggerOffTime = currentTime;
}

void Enveloppe::setAttackTime(float attack) {
    _attackTime = attack;
}

void Enveloppe::setReleaseTime(float release) {
    _releaseTime = release;
}

void Enveloppe::updateAmplitude() {
    switch (_stage) {
        case Stage::ATTACK:
            _amplitude += 1.0f / (Constants::SAMPLE_RATE * _attackTime);
            if (_amplitude >= 1.0f) {
                _amplitude = 1.0f;
                _stage = Stage::SUSTAIN;
            }
            break;
        case Stage::SUSTAIN:
            _amplitude = 1.0f;
            break;
        case Stage::RELEASE:
            _amplitude -= 1.0f / (Constants::SAMPLE_RATE * _releaseTime);
            if (_amplitude <= 0.0f) {
                _amplitude = 0.0f;
                _stage = Stage::OFF;
            }
            break;
        case Stage::OFF:
            _amplitude = 0.0f;
            break;
    }
}

void Enveloppe::updateStage(double time) {
    if (_stage == Stage::ATTACK && time - _triggerOnTime > _attackTime) {
        _stage = Stage::SUSTAIN;
    } else if (_stage == Stage::RELEASE && time - _triggerOffTime > _releaseTime) {
        _stage = Stage::OFF;
    }
}
