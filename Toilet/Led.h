#ifndef Led_h
#define Led_h
#include <Arduino.h>

namespace Washlet
{
    class Led
    {
    public:
        static const uint8_t Red = 27;
        static const uint8_t Blue = 32;
        static const uint8_t Green = 33;
        Led(uint8_t gpio);
        void Flash();

    private:
        uint8_t gpio;
    };
}
#endif