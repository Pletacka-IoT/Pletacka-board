#pragma once

#include <Arduino.h>

// #include "gridui.h"
#include "rbprotocol.h"
// #include "rbwebserver.h"
// #include "rbwifi.h"

#include <TFT_eSPI.h>
#include "WiFi.h"
#include <WiFiClient.h>
#include "pletacka_config.hpp"

using namespace rb;





class Pletacka_UI
{
    private:
        int bcgColour = TFT_BLACK;
        int blockColour = TFT_BLUE;
        int textColour = TFT_WHITE;
        int errorColour = TFT_RED;
        int radius = 4;

        PletackaConfig* pCfg = nullptr;
		Protocol* pProt = nullptr;
        
        // TFT_eSPI tft = TFT_eSPI();
        

    public:
		TFT_eSPI tft = TFT_eSPI(135, 240);

		void init(PletackaConfig* inCfg, rb::Protocol* inProt);

        void displayInit();
        void showId(int number);
        void showError(String msg, int colour = TFT_RED);
        void hideError();
        void showMsg(String msg);
        void hideMsg();
        void showStatus(String status);
        void hideStatus();
        // void showSend();
        // void hideSend();
        void showStatusX(String status, int x);
		void sendLog(String text);
		void test();
        
};




