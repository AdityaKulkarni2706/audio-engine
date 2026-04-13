#include <gtest/gtest.h>
#include "../effects/Gain.h"
#include "../audio/AudioBuffer.h" 

// We are testing the Gain class, specifically the process/apply feature

// test catgry      test name
TEST(GainTest, HalvesVolumeWhenGainIsPointFive) {
    // 1. ARRANGE
    Gain gainEffect(0.5f); 
    
    // Create an audio block with predictable samples
    AudioBlock block;
    block.samples = { 1.0f, -0.8f, 0.0f, 0.5f };

    // 2. ACT
    gainEffect.process(block);

    // 3. ASSERT
    // We use EXPECT_FLOAT_EQ because comparing floats directly with == is dangerous in C++
    EXPECT_FLOAT_EQ(block.samples[0], 0.5f);
    EXPECT_FLOAT_EQ(block.samples[1], -0.4f);
    EXPECT_FLOAT_EQ(block.samples[2], 0.0f);
    EXPECT_FLOAT_EQ(block.samples[3], 0.25f);
}