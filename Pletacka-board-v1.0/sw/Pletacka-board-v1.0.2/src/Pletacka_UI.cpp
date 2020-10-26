#include "Pletacka_UI.hpp"

#define GRIDUI_LAYOUT_DEFINITION
#include "GiriUI_layout.hpp"
#include <string>


void Pletacka_UI::init(PletackaConfig* inCfg, rb::Protocol* inProt)
{
    pCfg = inCfg;
	pProt = inProt;

	displayInit();
	showId(pCfg->sensorNumber);


    pProt = new Protocol("Pletacka-IoT", "Pletacka" , "Compiled at " __DATE__ " " __TIME__, [](const std::string& cmd, rbjson::Object* pkt) {
		if (UI.handleRbPacket(cmd, pkt))
			return;
	});    
	pProt->start();

    // Start serving the web page
    rb_web_start(80);

    // Initialize the UI builder
    UI.begin(pProt);

    auto builder = Layout.begin();

	Layout.numberInfo.setText(String(pCfg->sensorNumber).c_str());
	Layout.numberText.setText(String(pCfg->sensorNumber).c_str());

	builder.rebootButton
	.onPress([](Button&) {
		printf("Reboot\n");
		ESP_LOGE("", "Reboot2");
	});

    builder.numberPlus
        .onPress([&](Button&) {
			pCfg->sensorNumber++;
			Layout.numberInfo.setText(String(pCfg->sensorNumber).c_str());
			Layout.numberText.setText(String(pCfg->sensorNumber).c_str());
			Serial.printf("PLus - %d\n", pCfg->sensorNumber);
        });	

    builder.numberMinus
        .onPress([&](Button&) {
			pCfg->sensorNumber--;			
			Layout.numberInfo.setText(String(pCfg->sensorNumber).c_str());
			Layout.numberText.setText(String(pCfg->sensorNumber).c_str());
			Serial.printf("Minus - %d\n", pCfg->sensorNumber);
        });	

    builder.numberSave
        .onPress([&](Button&) {
			// pCfg->sensorNumber;			
			// Layout.numberInfo.setText(String(pCfg->sensorNumber).c_str());
			// Layout.numberText.setText(String(pCfg->sensorNumber).c_str());
			Serial.printf("Save - %d\n", pCfg->sensorNumber);
        });		

	builder.commit();
}

///////////////////////////LOG/////////////////////////

void Pletacka_UI::sendLog(String text, String logLevel)
{
	String msg = "["+logLevel+"] " +text;

	Serial.println(msg);
	
	if(pCfg->debugOn)
	{
		pProt->send_log(msg.c_str());
	}
}

void Pletacka_UI::sendLogNoLn(String text, String logLevel)
{
	String msg = "["+logLevel+"] " +text;

	Serial.print(msg);
	
	if(pCfg->debugOn)
	{
		pProt->send_log(msg.c_str());
	}
}

///////////////////////////SERIAL/////////////////////////

void Pletacka_UI::print(String text)
{
	sendLogNoLn(text, "SERIAL");
}

void Pletacka_UI::println(String text)
{
	print(text);
	Serial.println();
}

void Pletacka_UI::debug(String text)
{
	if(pCfg->debugOn)
	{	
		sendLogNoLn(text, "DEBUG");
	}
}

void Pletacka_UI::debugln(String text)
{
	if(pCfg->debugOn)
	{	
		debug(text);
		Serial.println();
	}
}

///////////////////////////DISPLAY/////////////////////////

void Pletacka_UI::displayInit()
{  
    tft.init();
    tft.fontHeight(2);
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(textColour);
}

void Pletacka_UI::showId(int number)
{
    tft.fillCircle(12, 12,  12, TFT_DARKGREEN);
    tft.drawCentreString(String(number), 12, 5 , 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
}


void Pletacka_UI::showError(String msg, int colour )
{
    tft.fillRoundRect(0, tft.height()- 20,  tft.width(), 20, radius, colour);
    tft.drawString(msg, 5,tft.height()-17, 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
	sendLog(msg, "D: showError");
	
}

void Pletacka_UI::hideError()
{
    tft.fillRoundRect(0, tft.height()- 15,  tft.width(), 15, radius, bcgColour);
}


void Pletacka_UI::showMsg(String msg)
{
    tft.fillRoundRect(105, 0,  135, 24, radius, blockColour);
    tft.drawString(msg, 110, 5, 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
	sendLog(msg, "D: showMsg");
}

void Pletacka_UI::hideMsg()
{
    tft.fillRoundRect(105, 0,  135, 24, radius, blockColour);
}

void Pletacka_UI::showStatus(String status)
{
    int bcgCol;

    if(status == "ON")
    {
        bcgCol = TFT_BLUE;
    }
    else if (status == "STOP")
    {
        bcgCol = TFT_RED;
    }
    else if (status == "REWORK")
    {
        bcgCol = TFT_YELLOW;
    }
    else
    {
        bcgCol = TFT_DARKGREEN;
    }


    tft.fillRoundRect(40, 50,  160, 45, radius, bcgCol);

    tft.setTextColor(TFT_WHITE);
    tft.drawCentreString(status, 120, 62, 4);  //string,start x,start y, font weight {1;2;4;6;7;8}


}

void Pletacka_UI::hideStatus()
{
    tft.fillRoundRect(40, 50,  160, 45, radius, TFT_BLACK);
}






///////////////////////////DISPLAY/////////////////////////

