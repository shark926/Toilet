#include "Detector.h"

namespace Washlet
{
    Detector::Detector()
    {
    }

    Detector::~Detector()
    {
    }

    void Detector::Init(uint8_t io)
    {
        gpio = io;
        pinMode(gpio, INPUT);
    }

    bool Detector::CheckState()
    {
        return digitalRead(gpio) == HIGH;
    }
}