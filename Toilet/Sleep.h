#pragma once
#include "MyGpio.h"

namespace Washlet
{
    class Sleep
    {
    public:
        Sleep(gpio_num_t gpio, uint8_t mode, int level);
        ~Sleep();

        void Start();
        void PrintWakeupInfo();
    };
}