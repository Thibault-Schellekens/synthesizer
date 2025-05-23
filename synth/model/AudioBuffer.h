//
// Created by schel.
//

#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H
#include <vector>

struct AudioBuffer {
    std::vector<float> buffer;

    explicit AudioBuffer(const std::size_t size) : buffer(size) {}
};

#endif //AUDIOBUFFER_H
