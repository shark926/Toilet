#include "Led.h"
#include "Net.h"
#include "TouchPad.h"
#include "MyGpio.h"
#include "Sleep.h"

using namespace Washlet;

# include "config.h"

const uint16_t hostPort = 8266;         //主机端口
const uint16_t localPort = 8266;         //主机端口

//uint8_t test[6] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46}; //6个字节的测试数据
uint8_t state[2] = {0, 0};

MyGpio* pGpio0;
//MyGpio pGpio1;

Sleep* pSleep;
Led* pTouchLed;
Net* pNet;
 
void setup()
{
    Serial.begin(115200);
    
    pGpio0 = new MyGpio(GPIO_NUM_2, INPUT_PULLDOWN);

    pSleep = new Sleep(pGpio0, HIGH);
    pSleep->PrintWakeupInfo();

    pTouchLed = new Led(Led::Red);

    pNet = new Net(localPort, host, hostPort);
    pNet->ConnectRouter(WIFISSID, Password);
}

void loop()
{
    bool touched0 = pGpio0->IsHigh();
    bool touched1 = false;

    state[0] = touched0 == true;
    state[1] = touched1 == true;
    
    if(touched0 || touched1)
    {
        pNet->Send(state, sizeof(state));
        pTouchLed->Flash();
        Serial.println("touched");
    }
    else
    {
        pSleep->Start();
    }
    
    delay(1000);
}