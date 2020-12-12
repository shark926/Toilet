#pragma once
#include "MyGpio.h"

namespace Washlet
{
    class Sleep
    {
    private:
        MyGpio* pWakeupGpio;
    public:
        /**
         * ESP32 共有5 个Strapping 管脚。
         * MTDI/GPIO12：内部下拉
         * GPIO0：内部上拉
         * GPIO2：内部下拉
         * MTDO/GPIO15：内部上拉
         * GPIO5：内部上拉
        */
        Sleep(MyGpio* pWakeupGpio, int level);
        ~Sleep();

        void Start();
        void PrintWakeupInfo();
    };
}