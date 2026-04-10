#include <vector>

class CircularBuffer{
public:
    CircularBuffer() = default;
    void reset();
    void setSize(int size);
    float read(int delay) const;
    void write(float sample);
    int getWriteIdx() const;

private:
    std::vector<float> buffer;
    int writeIdx{0};

};