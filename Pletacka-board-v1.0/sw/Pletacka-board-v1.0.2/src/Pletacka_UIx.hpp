#pragma once

#include <Arduino.h>
#include "pletacka_config.hpp"
#include <TFT_eSPI.h>
#include "time.h"
#include "WiFi.h"
#include <WiFiClient.h>



class Pletacka_UIx
{
    private:
        int bcgColour = TFT_BLACK;
        int blockColour = TFT_BLUE;
        int textColour = TFT_WHITE;
        int errorColour = TFT_RED;
        int radius = 4;

        int *pletackaNumber = 0;

        struct tm tmx;
        
        
        

    public:
        TFT_eSPI tft = TFT_eSPI(135, 240);
        void displayInit(PletackaConfig* config);
        void timeInit();
        void showId(int number);
        void showTime();
        void showError(String msg, int colour = TFT_RED);
        void hideError();
        void showMsg(String msg);
        void hideMsg();
        void showStatus(String status);
        void hideStatus();
        // void showSend();
        // void hideSend();
        void showStatusX(String status, int x);
        
};




