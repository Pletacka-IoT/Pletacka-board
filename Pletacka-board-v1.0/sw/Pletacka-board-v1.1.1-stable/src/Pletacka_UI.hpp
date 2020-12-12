#pragma once

#include <Arduino.h>

#include "gridui.h"
#include "rbprotocol.h"
#include "rbwebserver.h"
#include "rbwifi.h"

#include <TFT_eSPI.h>
#include "WiFi.h"
#include <WiFiClient.h>
#include "Pletacka_config.hpp"
#include "EEPROM.h"

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

		int cFinished = 0;
		unsigned long tStopNow = 0;
		int tStopAll = 0;
		String iName;
		int iBgCol = TFT_OLIVE;
		unsigned long iStartOfStopState = 0;


        PletackaConfig* pCfg = nullptr;
		Protocol* pProt = nullptr;
        
		// gridui::builder::_LayoutBuilder* Lay = nullptr;
		
        // TFT_eSPI tft = TFT_eSPI();
        

    public:
		TFT_eSPI tft = TFT_eSPI(135, 240);
		EEPROMClass eeprom;

		void init(PletackaConfig* inCfg);
		void initUIGrid(rb::Protocol* inProtvoid);
		void sendLog(String text, String logLevel, bool sendToApp = true);
        
		void print(String text, bool sendToApp = true);
		void println(String text, bool sendToApp = true);
		void debug(String text, bool sendToApp = true);
		void debugln(String text, bool sendToApp = true);
		void UIoffLeds();

		void displayInit();
        void showId();
        void showError(String msg, int colour = TFT_RED, bool sendToApp = true);
        void hideError();
        void showMsg(String msg, bool sendToApp = true);
        void hideMsg();
        void showStatus(String status, bool sendToApp = true);
        void hideStatus();
        void updateInfo(String status, bool sendToApp = true);
		void showInfo();
        void hideInfo();

		void changeID();

		// gridui::_Layout* layout(){return &Layout;}
		

		
        
};




