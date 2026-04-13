#include <gtest/gtest.h>
#include "../audio/BlockUtils.h"
#include "audio/AudioBuffer.h"

TEST(BlockUtilsTest, DeinterleavesStereoToTwoMonoChannels){
    AudioClip testClip;
    testClip.samples = {1.0f, -1.0f, 0.5f, -0.5f};
    testClip.numChannels = 2;
    testClip.numFrames = 2;

    std::vector<AudioClip> deinterleavedClips = deinterleave(testClip);
    
    EXPECT_FLOAT_EQ(deinterleavedClips[0].samples[0], 1.0f);
    EXPECT_FLOAT_EQ(deinterleavedClips[0].samples[1], 0.5f);
    EXPECT_FLOAT_EQ(deinterleavedClips[1].samples[0], -1.0f);
    EXPECT_FLOAT_EQ(deinterleavedClips[1].samples[1], -0.5f);

}

TEST(BlockUtilsTest, InterleavesTwoMonoChannelsToStereo){
    AudioClip monoChannel1;
    monoChannel1.samples = {1.0f, 2.0f};
    monoChannel1.numFrames = 2;
    monoChannel1.numChannels = 1;

    AudioClip monoChannel2;
    monoChannel2.samples = {-1.0f, -2.0f};
    monoChannel2.numFrames = 2;
    monoChannel2.numChannels = 1;

    std::vector<AudioClip> testMonoChannels = {monoChannel1, monoChannel2};
    
    AudioClip interleavedClip = interleave(testMonoChannels);

    EXPECT_FLOAT_EQ(interleavedClip.samples[0], 1.0f);
    EXPECT_FLOAT_EQ(interleavedClip.samples[1], -1.0f);
    EXPECT_FLOAT_EQ(interleavedClip.samples[2], 2.0f);
    EXPECT_FLOAT_EQ(interleavedClip.samples[3], -2.0f);

}

TEST(BlockUtilsTest, splitIntoBlocksAddsPaddingToFinalBlock){
    AudioClip testClip;
    testClip.samples = std::vector<float>(1023, 1.0f);
    testClip.numFrames = 1023;
    testClip.numChannels = 1;
    size_t blockSize = 512;

    std::vector<AudioBlock> blocks = splitIntoBlocks(testClip, blockSize);
    EXPECT_EQ(blocks.size(), 2);
    EXPECT_EQ(blocks[1].samples[511], 0);

}