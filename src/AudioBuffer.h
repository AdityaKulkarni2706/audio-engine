#pragma once
#include <cstddef>
#include <vector>

struct AudioBuffer {
    std::vector<float> samples;
    int sampleRate = 0;
    int numChannels = 0;
    size_t numFrames = 0;
};

