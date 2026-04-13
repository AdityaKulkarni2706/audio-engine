#include <gtest/gtest.h>
#include "../audio/BlockUtils.h"
#include "audio/AudioBuffer.h"

TEST(BlockUtilsTest, DeinterleavesStereoToMonoChannels){
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