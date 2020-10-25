#pragma once

#include <Arduino.h>
#include "pletacka_config.hpp"
#include "Pletacka_display.hpp"
#include <WiFi.h>

class Pletacka_wifi
{
private:
    struct wifiConfig
    {
        wifiConfig()
            : wifiName("")
            , wifiPassword("")
            , wifiChanel(1)
            , wifiDefaulAp(false)
            , apName("")
            , apPassword("")
            , apChanel(1) {
        }
        
        String wifiName;    //WiFi name
        String wifiPassword;//WiFi password
        int wifiChanel;     //WiFi chanel
        bool wifiDefaulAp;  //Run AP on startup
        String apName;      //AP name
        String apPassword;  //AP password
        int apChanel;       //AP chanel
    };

    wifiConfig wifiCfg;

	int sensorNumber = 1;

	Pletacka_display* pletacka_display = nullptr;
    
public:
    Pletacka_wifi();
    ~Pletacka_wifi();
    void init(PletackaConfig* config, Pletacka_display* pletacka_dis);
    void configConnection();
    void connectWifi();
    void startAP();
};


