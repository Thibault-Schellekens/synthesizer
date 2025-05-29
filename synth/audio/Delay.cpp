//
// Created by schel.
//

#include "Delay.h"

Delay::Delay() {
    updateIndex();
}

void Delay::processAudioBuffer(AudioBuffer &audioBuffer) {
    if (_delayMix <= 0.0f)
        return;

    for (unsigned frame = 0; frame < Constants::FRAMES_PER_BUFFER; ++frame) {
        const float delayedSample = _delayBuffer.buffer[_readIndex];

        const float mixedSample = audioBuffer.buffer[frame] + (delayedSample * _delayMix);

        audioBuffer.buffer[frame] = mixedSample;
        _delayBuffer.buffer[_writeIndex] = mixedSample;

        _readIndex = (_readIndex + 1) % _delayBuffer.buffer.size();
        _writeIndex = (_writeIndex + 1) % _delayBuffer.buffer.size();
    }
}

void Delay::setDelayTime(float delayTime) {
    _delayTime = delayTime;
    updateIndex();
}

void Delay::setDelayMix(float delayMix) {
    _delayMix = delayMix;

    if (_delayMix <= 0.0f)
        std::fill(_delayBuffer.buffer.begin(), _delayBuffer.buffer.end(), 0.0f);
}

void Delay::updateIndex() {
    const int delaySamples = static_cast<int>(_delayTime * Constants::SAMPLE_RATE);

    _writeIndex = (_readIndex + delaySamples) % _delayBuffer.buffer.size();
}
