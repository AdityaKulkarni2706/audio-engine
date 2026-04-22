#include <vector>
#include "AudioBuffer.h"
#include <iostream>

std::vector<AudioBuffer> splitIntoBlocks(const AudioBuffer& clip, size_t blockSize);
AudioBuffer mergeBlocks(const std::vector<AudioBuffer>& blocks);
std::vector<AudioBuffer> deinterleave(const AudioBuffer& clip);
AudioBuffer interleave(const std::vector<AudioBuffer>& clips);
