#pragma once
#include <string>
#include <memory>
#include "AudioBuffer.h"
#include "../effects/EffectChain.h"
#include "../effects/Effect.h"


class AudioEngine{
public:
    AudioEngine(const std::string& inputPath,
                const std::string& outputPath,
                size_t bufferSize = 512);
    
    void addEffect(std::unique_ptr<Effect> effect);
    void run();
private:
    std::string inputPath;
    std::string outputPath;
    size_t blockSize;
    EffectChain templateChain;
};
