#include "net.h"

namespace Washlet
{
    Net::Net(uint16_t localPort, const char *host, uint16_t port):localPort(localPort), host(host), hostPort(port)
    {
    }

    Net::~Net()
    {
    }

    void Net::ConnectRouter(const char* ssid, const char *passphrase)
    {
        // We start by connecting to a WiFi network
        wiFiMulti.addAP(ssid, passphrase);

        Serial.println();
        Serial.println();
        Serial.print("Wait for WiFi... ");

        while (wiFiMulti.run() != WL_CONNECTED)
        {
            Serial.print(".");
            delay(500);
        }

        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        delay(500);
    }

    void Net::Send(uint8_t* data, uint8_t length)
    {
        udp.begin(WiFi.localIP(), localPort);
        udp.beginPacket(host, hostPort);
        udp.write(data, length);
        //Serial.println("send end");
        // Buf_Size=udp.parsePacket();
        // udp.read(RxBuf,Buf_Size);
        // Serial.write(RxBuf,Buf_Size);
      
        udp.endPacket();
        delay(500);
    }
}