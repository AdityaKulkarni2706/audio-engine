#pragma once
#include "AudioBuffer.h"

class Effect{
public:
    virtual ~Effect() = default;
    virtual void process(AudioBuffer& Buffer) = 0;

    // Every effect must have a process
};