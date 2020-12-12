#pragma once
#include <Arduino.h>

namespace Washlet
{
    class MyGpio
    {
    private:
        gpio_num_t num;
    public:
        MyGpio(gpio_num_t num, uint8_t mode);
        ~MyGpio();

        gpio_num_t GetNum() const;
        bool IsHigh() const;
    };
}