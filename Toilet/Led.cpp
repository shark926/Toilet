#include "Led.h"

namespace Washlet
{
    Led::Led(uint8_t gpio)
    {
        this->gpio = gpio;
        pinMode(gpio, OUTPUT);
        digitalWrite(gpio, HIGH);
    }

    void Led::Flash()
    {
        digitalWrite(gpio, LOW);
        delay(50);
        digitalWrite(gpio, HIGH);
        //delay(100);
    }
}