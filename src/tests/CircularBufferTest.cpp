#include <gtest/gtest.h>
#include "../dsp/CircularBuffer.h"

TEST(CircularBufferTest, PushesAndPopsValuesCorrectly){
    CircularBuffer testBuffer;
    testBuffer.setSize(2);
    testBuffer.write(0.5f);

    float value = testBuffer.read(1);
    EXPECT_FLOAT_EQ(value, 0.5f);

}

TEST(CircularBufferTest, WrapsAroundWhenCapacityIsReached){
    CircularBuffer testBuffer;
    testBuffer.setSize(3);
    testBuffer.write(1);
    testBuffer.write(2);
    testBuffer.write(3);
    testBuffer.write(4);
    EXPECT_FLOAT_EQ(testBuffer.read(1), 4);
    EXPECT_FLOAT_EQ(testBuffer.read(2), 3);
    EXPECT_FLOAT_EQ(testBuffer.read(3), 2);

}

TEST(CircularBufferTest, ReturnsZeroWhenReadingValuesBeforeBufferHasData){
    CircularBuffer testBuffer;
    testBuffer.setSize(3);
    EXPECT_FLOAT_EQ(testBuffer.read(3), 0.0f);
    
}