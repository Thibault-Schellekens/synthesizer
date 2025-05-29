//
// Created by schel.
//

#include "Envelope.h"

#include <iostream>
#include <ostream>

#include "constants.h"

void Envelope::processAudioBuffer(AudioBuffer &audioBuffer) {
    for (int frame = 0; frame < Constants::FRAMES_PER_BUFFER; ++frame) {
        updateAmplitude();
        audioBuffer.buffer[frame] *= _amplitude;
    }
}

void Envelope::noteOn() {
        _stage = Stage::ATTACK;
}

void Envelope::noteOff() {
        _stage = Stage::RELEASE;
}

void Envelope::setAttackTime(float attack) {
    _attackTime = attack;
}

void Envelope::setReleaseTime(float release) {
    _releaseTime = release;
}

void Envelope::updateAmplitude() {
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
