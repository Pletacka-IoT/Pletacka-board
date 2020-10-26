#pragma once

#include <Arduino.h>

#include "gridui.h"
#include "rbprotocol.h"
#include "rbwebserver.h"
#include "rbwifi.h"

#include <TFT_eSPI.h>
#include "WiFi.h"
#include <WiFiClient.h>
#include "pletacka_config.hpp"


using namespace rb;
using namespace gridui;





class Pletacka_UI
{
    private:
		void sendLogNoLn(String text, String logLevel, bool sendToApp = true);

        int bcgColour = TFT_BLACK;
        int blockColour = TFT_BLUE;
        int textColour = TFT_WHITE;
        int errorColour = TFT_RED;
        int radius = 4;

        PletackaConfig* pCfg = nullptr;
		Protocol* pProt = nullptr;
        
		// gridui::builder::_LayoutBuilder* Lay = nullptr;
		
        // TFT_eSPI tft = TFT_eSPI();
        

    public:
		TFT_eSPI tft = TFT_eSPI(135, 240);

		void init(PletackaConfig* inCfg);
		void initUIGrid(rb::Protocol* inProt);

		void sendLog(String text, String logLevel, bool sendToApp = true);
        
		void print(String text, bool sendToApp = true);
		void println(String text, bool sendToApp = true);
		void debug(String text, bool sendToApp = true);
		void debugln(String text, bool sendToApp = true);

		void displayInit();
        void showId(int number);
        void showError(String msg, int colour = TFT_RED, bool sendToApp = true);
        void hideError();
        void showMsg(String msg, bool sendToApp = true);
        void hideMsg();
        void showStatus(String status, bool sendToApp = true);
        void hideStatus();

		// gridui::_Layout* layout(){return &Layout;}
		

		
        
};




