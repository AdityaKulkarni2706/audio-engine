#include <iostream>
#include "AudioFileIO.h"

int main(){
    AudioFileIO fileIo;
    AudioBuffer buffer = fileIo.readWav("../input.wav");

    std::cout << "Loaded file\n";
    std::cout << "Sample rate: " << buffer.sampleRate << "\n";

    fileIo.writeWav("../output.wav", buffer);

    std::cout << "Wrote output.wav\n";
}
