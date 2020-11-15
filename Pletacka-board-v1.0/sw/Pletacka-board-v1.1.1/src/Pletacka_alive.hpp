#pragma once

#include <Arduino.h>
#include "Pletacka_config.hpp"
#include <WiFi.h>
#include <WiFiUdp.h>
#include "Pletacka_UI.hpp"


class Pletacka_alive
{
private:
	PletackaConfig* cfg = nullptr;
    WiFiUDP udp;
    IPAddress udpIP;

	Pletacka_UI* UI = nullptr;
    
public:
    Pletacka_alive();
    ~Pletacka_alive();
    void init(PletackaConfig* config, Pletacka_UI* inUI);
    void sendAlive(int sensorNumber);

};


