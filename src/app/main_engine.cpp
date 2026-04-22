#include "audio/AudioEngine.h"
#include "effects/Gain.h"
#include "effects/ffDelay.h"

int main() {
    AudioEngine engine("./input.wav", "./output.wav");

    // Add ur effects here
    engine.addEffect(std::make_unique<Gain>(1.0f));
    engine.addEffect(std::make_unique<ffDelay>(15000, 1.0f, 44100));

    engine.run();
    return 0;
}