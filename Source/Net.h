#ifndef NET_H
#define NET_H

#include <WiFi.h>
#include <WiFiUDP.h>
#include <WiFiMulti.h>

namespace Washlet
{
    class Net
    {
    private:
        const char *host; // ip or dns 远程主机ip
        uint16_t hostPort;//主机端口

        uint16_t localPort;

        WiFiMulti wiFiMulti;
        WiFiUDP udp;
    public:
        Net(uint16_t localPort, const char *host, uint16_t port);
        ~Net();

        void ConnectRouter(const char* ssid, const char *passphrase);
        void Send(uint8_t* data, uint8_t length);
    };
}

#endif