#include "Effect.h"
#include "../audio/AudioBuffer.h"

class Gain : public Effect{
public:
    Gain() = default;
    explicit Gain(float gainAmount);

    void process(AudioBuffer& buffer) override;

    void setGain(float newGain);
    float getGain() const;
    std::unique_ptr<Effect> clone() const override;

private:
    float gain = 1.0f;

};