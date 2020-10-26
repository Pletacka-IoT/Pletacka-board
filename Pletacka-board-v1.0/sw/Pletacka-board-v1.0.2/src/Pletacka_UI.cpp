#include "Pletacka_UI.hpp"

#define GRIDUI_LAYOUT_DEFINITION
#include "GiriUI_layout.hpp"
#include <string>


void Pletacka_UI::init(PletackaConfig* inCfg)
{
    pCfg = inCfg;

	displayInit();
	showId(pCfg->sensorNumber);



}

void Pletacka_UI::initUIGrid(rb::Protocol* inProt)
{
	pProt = inProt;

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
		static int num = 3;
		if(num<=0)
		{
			Layout.rebootButton.setText("Rebooting now");
			Layout.stateText.setText("Rebooting now");
			delay(500);
			ESP.restart();
		}
		else
		{
			Layout.rebootButton.setText(String("Reboot - "+String(num)).c_str());
			num--;
		}
		
		// printf("Reboot\n");
	});

    builder.numberPlus
        .onPress([&](Button&) {
			pCfg->sensorNumber++;
			Layout.numberSave.setText("Save");
			Layout.numberInfo.setText(String(pCfg->sensorNumber).c_str());
			Layout.numberText.setText(String(pCfg->sensorNumber).c_str());
			sendLog("Snum ++", "Num: " + String(pCfg->sensorNumber));
        });	

    builder.numberMinus
        .onPress([&](Button&) {
			pCfg->sensorNumber--;	
			Layout.numberSave.setText("Save");		
			Layout.numberInfo.setText(String(pCfg->sensorNumber).c_str());
			Layout.numberText.setText(String(pCfg->sensorNumber).c_str());
			sendLog("Snum --", "Num: " + String(pCfg->sensorNumber));
        });	

    builder.numberSave
        .onPress([&](Button&) {
			Layout.numberSave.setText("SAVED");
			sendLog("Snum SAVE", "Num: " + String(pCfg->sensorNumber));
        });		

	builder.commit();
}

///////////////////////////LOG/////////////////////////

void Pletacka_UI::sendLogNoLn(String text, String logLevel, bool sendToApp)
{
	String msg = "["+logLevel+"] " +text;

	Serial.print(msg);

	if(sendToApp && pCfg->debugOn)
	{
		if(pProt == nullptr)
		{
			ESP_LOGE(TAG, "Protocol not initialized!");
			return;
		}
		else
		{
			pProt->send_log(msg.c_str());
		}
	}
}

void Pletacka_UI::sendLog(String text, String logLevel, bool sendToApp)
{
	sendLogNoLn(text, logLevel, sendToApp);
	Serial.println();
}

///////////////////////////SERIAL/////////////////////////

void Pletacka_UI::print(String text, bool sendToApp)
{
	sendLogNoLn(text, "SERIAL", sendToApp);
}

void Pletacka_UI::println(String text, bool sendToApp)
{
	print(text, sendToApp);
	Serial.println();
}

void Pletacka_UI::debug(String text, bool sendToApp)
{
	if(pCfg->debugOn)
	{	
		sendLogNoLn(text, "DEBUG", sendToApp);
	}
}

void Pletacka_UI::debugln(String text, bool sendToApp)
{
	if(pCfg->debugOn)
	{	
		debug(text, sendToApp);
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


void Pletacka_UI::showError(String msg, int colour, bool sendToApp)
{
    tft.fillRoundRect(0, tft.height()- 20,  tft.width(), 20, radius, colour);
    tft.drawString(msg, 5,tft.height()-17, 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
	sendLog(msg, "DISP: showError", sendToApp);
	
}

void Pletacka_UI::hideError()
{
    tft.fillRoundRect(0, tft.height()- 15,  tft.width(), 15, radius, bcgColour);
}


void Pletacka_UI::showMsg(String msg, bool sendToApp)
{
    
	tft.fillRoundRect(105, 0,  135, 24, radius, blockColour);
    tft.drawString(msg, 110, 5, 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
	sendLog(msg, "DISP: showMsg", sendToApp);
}

void Pletacka_UI::hideMsg()
{
    tft.fillRoundRect(105, 0,  135, 24, radius, blockColour);
}

void Pletacka_UI::showStatus(String status, bool sendToApp)
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

	sendLog(status, "DISP: showStatus", sendToApp);
}

void Pletacka_UI::hideStatus()
{
    tft.fillRoundRect(40, 50,  160, 45, radius, TFT_BLACK);
}






///////////////////////////DISPLAY/////////////////////////

