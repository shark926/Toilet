#ifndef DETECTOR_H
#define DETECTOR_H

#include<Arduino.h>

namespace Washlet
{
    class Detector
    {
    private:
        uint8_t gpio;
    public:
        Detector();
        ~Detector();
        void Init(uint8_t io);
        bool CheckState();
    };
}
#endif