#ifndef TOUCH_PAD_h
#define TOUCH_PAD_h

#include "Arduino.h"

namespace Washlet
{
    class TouchPad
    {
    private:
        static const uint8_t TouchedValueThrottle = 15;

    public:
        TouchPad(/* args */);
        ~TouchPad();

        bool IsT1Touched();
        bool IsT2Touched();
    };
}
#endif