#include "Sleep.h"

namespace Washlet
{
    /**
     * ESP32 共有5 个Strapping 管脚。
     * MTDI/GPIO12：内部下拉
     * GPIO2：内部下拉
     * GPIO0：内部上拉
     * MTDO/GPIO15：内部上拉
     * GPIO5：内部上拉
    */
    Sleep::Sleep(gpio_num_t gpio, uint8_t mode, int level)
    {
        pinMode(gpio, mode);
        esp_sleep_enable_ext0_wakeup(gpio, level);
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