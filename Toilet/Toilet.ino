#include "Led.h"
#include "Net.h"
#include "TouchPad.h"
#include "MyGpio.h"
#include "Sleep.h"

using namespace Washlet;

#include "config.h"

static const uint16_t hostPort = 8266;         //主机端口
static const uint16_t localPort = 8266;         //主机端口
//static const gpio_num_t gpioArray[]={GPIO_NUM_2, GPIO_NUM_12};
//static const gpio_num_t gpioArray[]={GPIO_NUM_2};
static const gpio_num_t gpioArray[]={GPIO_NUM_12};
//uint8_t test[6] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46}; //6个字节的测试数据

static int gpioCount;
static uint8_t* sendData;

static MyGpio** pGpioArray;

static Sleep* pSleep;
static Led* pTouchLed;
static Net* pNet;
 
void setup()
{
    Serial.begin(115200);
    
    gpioCount = sizeof(gpioArray);

    sendData = new uint8_t[gpioCount];

    pGpioArray = new MyGpio*[gpioCount];
    for (size_t i = 0; i < gpioCount; i++)
    {
        pGpioArray[i] = new MyGpio(gpioArray[i], INPUT_PULLDOWN);
    }

    pSleep = new Sleep(pGpioArray, gpioCount,HIGH);
    pSleep->PrintWakeupInfo();

    pTouchLed = new Led(Led::Red);

    pNet = new Net(localPort, host, hostPort);
    pNet->ConnectRouter(WIFISSID, Password);
}

void loop()
{
    bool touched = false;
    for (size_t i = 0; i < gpioCount; i++)
    {
        sendData[i] = pGpioArray[i]->IsHigh();

        if(sendData[i] != 0)
        {
           touched = true; 
        }
    }
    
    if(touched)
    {
        pNet->Send(sendData, gpioCount);
        pTouchLed->Flash();
        Serial.println("touched");
    }
    else
    {
        //Serial.println("not touched");
        pSleep->Start();
    }
    
    delay(1000);
}