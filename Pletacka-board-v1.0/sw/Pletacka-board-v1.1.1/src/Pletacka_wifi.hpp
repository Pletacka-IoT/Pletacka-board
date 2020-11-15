#pragma once

#include <Arduino.h>
#include "Pletacka_config.hpp"
#include "Pletacka_UI.hpp"
#include <WiFi.h>

class Pletacka_wifi
{
private:
	int sensorNumber = 1;
	PletackaConfig* cfg = nullptr;
	Pletacka_UI* UI = nullptr;
	WiFiClass pWiFi;
    
public:
    Pletacka_wifi();
    ~Pletacka_wifi();
    void init(PletackaConfig* config, Pletacka_UI* inUI);
    void connectWifi();
	// String Pletacka_wifi::getIP(pWiFi.)
};


