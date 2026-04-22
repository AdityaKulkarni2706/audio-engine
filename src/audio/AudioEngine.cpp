#include "AudioEngine.h"
#include "AudioBuffer.h"
#include "BlockUtils.h"
#include "../io/AudioFileIO.h"
#include "effects/EffectChain.h"
#include <iostream>

AudioEngine::AudioEngine(const std::string& inputPath,
                         const std::string& outputPath,
                         size_t blockSize)
    : inputPath(inputPath), outputPath(outputPath), blockSize(blockSize) {}

void AudioEngine::addEffect(std::unique_ptr<Effect> effect) {
    templateChain.addEffect(std::move(effect));
}

void AudioEngine::run(){
    // Read
    AudioFileIO fileIO;
    AudioBuffer clip = fileIO.readWav(inputPath);
    const int channels = clip.numChannels;
    std::cout << "Loaded: " << inputPath << "\n";
    std::cout << "Channels: " << channels << "  Frames: "
    << clip.numFrames << "  Sample rate: " << clip.sampleRate << "\n";

    // Deinterleave into one mono-buffer per channel
    std::vector<AudioBuffer> channelClips = deinterleave(clip);

    /*
        Cloning: Each channel must get its own independent effect
        instance. So if we have a standard audio broken down into LR channels,
        we need separate effect chains for L and R respectively.
    */
    std::vector<EffectChain> chains;
    chains.reserve(channels);
    for (int ch=0; ch < channels; ++ch){
        chains.push_back(templateChain.clone());
    }

    // Split channel into buffers/blocks
    std::vector<std::vector<AudioBuffer>> blocks;
    blocks.reserve(channels);
    for (int ch = 0; ch < channels; ++ch) {
        blocks.push_back(splitIntoBlocks(channelClips[ch], blockSize));
    }

    /*
        Note that processing below occurs 
        on arrays with the size of the buffer size.
    */
    for (int ch = 0; ch < channels; ++ch) {
        for (auto& block : blocks[ch]) {
            chains[ch].process(block);
        }
    }

    std::vector<AudioBuffer> finalClips;
    finalClips.reserve(channels);
    for (int ch = 0; ch < channels; ++ch) {
        finalClips.push_back(mergeBlocks(blocks[ch]));
    }

    AudioBuffer finalClip = interleave(finalClips);
    fileIO.writeWav(outputPath, finalClip);

    std::cout << "Wrote: " << outputPath << "\n";

}