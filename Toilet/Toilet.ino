#include "Led.h"
#include "Net.h"
#include "Detector.h"
#include "TouchPad.h"

using namespace Washlet;

# include "config.h"

const uint16_t hostPort = 8266;         //主机端口
const uint16_t localPort = 8266;         //主机端口

static const uint8_t DetectorIo0 = 34;
static const uint8_t DetectorIo1 = 35;

//uint8_t test[6] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46}; //6个字节的测试数据
uint8_t state[2] = {0, 0};
Detector detector0;
Detector detector1;
Led touchLed;
Led workingLed;
Net* net;

extern EspClass ESP;

void setup()
{
    Serial.begin(115200);

    detector0.Init(DetectorIo0);
    detector1.Init(DetectorIo1);

    touchLed.Init(Led::Red);
    workingLed.Init(Led::Green);

    net = new Net(localPort, host, hostPort);
    net->ConnectRouter(WIFISSID, Password);

    Serial.println("begin sleep");
    ESP.deepSleep(5000000);
    // Serial.println("light_sleep_enter");
    // esp_sleep_enable_timer_wakeup(10000000); //1 seconds
    // int ret = esp_light_sleep_start();
    // Serial.printf("light_sleep: %d\n", ret);
    
    Serial.println("end sleep");
}

void loop()
{
    bool touched0 = detector0.CheckState();
    bool touched1 = detector1.CheckState();

    state[0] = touched0 == true;
    state[1] = touched1 == true;
    
    
    if(touched0 || touched1)
    {
        net->Send(state, sizeof(state));
        touchLed.Flash();
        Serial.println("touched");
    }
    else
    {
        //用于测试记录电池工作时长
        net->Send(state, sizeof(state));
        workingLed.Flash();
        Serial.println("not touched");
    }
    
    delay(1000);
}