# include "MyGpio.h"

namespace Washlet
{
    MyGpio::MyGpio(gpio_num_t num, uint8_t mode)
    {
        this->num = num;

        pinMode(num, mode);
    }
    
    MyGpio::~MyGpio()
    {
    }
    
    gpio_num_t MyGpio::GetNum() const
    {
        return num;
    }

    bool MyGpio::IsLevel(int level) const
    {
        return digitalRead(num) == level;
    }
}