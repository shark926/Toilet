#include "touchPad.h"

namespace Washlet
{
    TouchPad::TouchPad(/* args */)
    {
    }

    TouchPad::~TouchPad()
    {
    }

    bool TouchPad::IsT1Touched()
    {
        int value = touchRead(T0);

        return value <= TouchedValueThrottle;
    }

    bool TouchPad::IsT2Touched()
    {
        int value = touchRead(T2);

        return value <= TouchedValueThrottle;
    }
}