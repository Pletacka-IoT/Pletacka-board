#pragma once

#include <Arduino.h>
#include "pletacka_config.hpp"
#include <WiFi.h>
#include <WiFiUdp.h>



class Pletacka_alive
{
private:
    struct udpConfig
    {
        udpConfig()
            : udpIP("192.168.0.112")
            , udpPort(2727)
 
            {
        }
        
        String udpIP;    //
        int udpPort;     //
    };

    udpConfig udpCfg;

    WiFiUDP udp;
    IPAddress udpIP;
    
public:
    Pletacka_alive();
    ~Pletacka_alive();
    void init(PletackaConfig config);
    void sendAlive(int sensorNumber);

};


