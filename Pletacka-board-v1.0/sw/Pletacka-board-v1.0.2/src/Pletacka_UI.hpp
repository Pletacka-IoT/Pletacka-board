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
// using namespace gridui;




class Pletacka_UI
{
    private:
        int bcgColour = TFT_BLACK;
        int blockColour = TFT_BLUE;
        int textColour = TFT_WHITE;
        int errorColour = TFT_RED;
        int radius = 4;

        PletackaConfig* cfg = nullptr;
		Protocol* gProt = nullptr;
        
        TFT_eSPI* dp;
        

    public:


		void init(PletackaConfig* config,  TFT_eSPI* inDp, Protocol* gProtocol);

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
        
};




