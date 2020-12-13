#include "Led.h"
#include "Net.h"
#include "TouchPad.h"
#include "MyGpio.h"
#include "Sleep.h"

using namespace Washlet;

#include "config.h"

static const uint16_t hostPort = 8266;         //主机端口
static const uint16_t localPort = 8266;         //主机端口

//只有GPIO_NUM_0, GPIO_NUM_5, GPIO_NUM_15这3个引脚有上拉功能
//0暂时用来下载程序，5用来唤醒，15用来读入数据。
//2个以上的输入源就需要外部上拉电路了
//实测GPIO_NUM_5不能唤醒
//GPIO_NUM_15可以唤醒
//GPIO_NUM_2, GPIO_NUM_12可以唤醒
/*******************************************/
static const uint8_t gpioMode = INPUT_PULLUP;
static const int wakeupLevel = LOW;
static const int triggerLevel = wakeupLevel;

static const gpio_num_t wakeupGpio = GPIO_NUM_15;
static const gpio_num_t gpioArray[]={GPIO_NUM_5};
/*******************************************/

static int gpioCount;
static uint8_t* sendData;

static MyGpio** pGpioArray;

static Sleep* pSleep;
static Led* pTriggerLed;
static Net* pNet;
 
void setup()
{
    Serial.begin(115200);
    
    gpioCount = sizeof(gpioArray)/sizeof(gpioArray[0]);

    Serial.printf("gpio count:%d\r\n", gpioCount);

    sendData = new uint8_t[gpioCount];

    pGpioArray = new MyGpio*[gpioCount];
    for (size_t i = 0; i < gpioCount; i++)
    {
        pGpioArray[i] = new MyGpio(gpioArray[i], gpioMode);
    }

    pSleep = new Sleep(wakeupGpio, gpioMode, wakeupLevel);
    pSleep->PrintWakeupInfo();

    pTriggerLed = new Led(Led::Red);

    pNet = new Net(localPort, host, hostPort);
    pNet->ConnectRouter(WIFISSID, Password);
}

void loop()
{
    bool triggered = false;
    for (size_t i = 0; i < gpioCount; i++)
    {
        sendData[i] = pGpioArray[i]->IsLevel(triggerLevel);

        if(sendData[i] != 0)
        {
           triggered = true; 
        }
    }
    
    if(triggered)
    {
        pNet->Send(sendData, gpioCount);
        pTriggerLed->Flash();
        Serial.println("triggered");
    }
    else
    {
        //Serial.println("not touched");
        pSleep->Start();
    }
    
    delay(1000);
}