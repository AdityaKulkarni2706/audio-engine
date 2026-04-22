#include "Gain.h"
#include "../audio/AudioBuffer.h"
#include <memory>

Gain::Gain(float gainAmount) : gain(gainAmount) {}

void Gain::process(AudioBuffer& buffer){
    for (auto& sample : buffer.samples){
        sample *= gain;
    }
}

void Gain::setGain(float newGain){
    gain = newGain;
}

float Gain::getGain() const{
    return gain;
}

std::unique_ptr<Effect> Gain::clone() const{
    return std::make_unique<Gain>(*this); 
}