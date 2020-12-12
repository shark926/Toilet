#include "Sleep.h"

namespace Washlet
{
    Sleep::Sleep(MyGpio* pWakeupGpio, int level)
    {
        this->pWakeupGpio = pWakeupGpio;
        esp_sleep_enable_ext0_wakeup(pWakeupGpio->GetNum(), level);
    }
    
    Sleep::~Sleep()
    {
    }
    
    void Sleep::Start()
    {
        Serial.println("ESP32 will sleep now!");
        esp_deep_sleep_start();
    }
    
    RTC_DATA_ATTR int bootCount = 0;
    void Sleep::PrintWakeupInfo()
    {
        Serial.printf("ESP32 is restart now! It's the %d time\r\n", ++bootCount);
  
        Serial.printf("the wakeup reason is :%d\r\n", esp_sleep_get_wakeup_cause());
    }
}