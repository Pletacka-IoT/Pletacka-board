#include "Pletacka_UI.hpp"

#define GRIDUI_LAYOUT_DEFINITION
#include "GiriUI_layout.hpp"
#include <string>


void Pletacka_UI::init(PletackaConfig* inCfg)
{
    pCfg = inCfg;

	eeprom.begin(50);
	if(eeprom.read(EEPROM_SNUMBER_A) == 255)
	{
		eeprom.write(EEPROM_SNUMBER_A, 33);
		eeprom.commit();
	}
	pCfg->sensorNumber = eeprom.read(EEPROM_SNUMBER_A);	

	displayInit();
	showId();


}

void Pletacka_UI::initUIGrid(rb::Protocol* inProt)
{
	// pProt = inProt;
    static constexpr size_t pletackaNameSize = 16;
	char *pletackaName = new char[pletackaNameSize];
	snprintf(pletackaName, pletackaNameSize, "Pletacka-%d", pCfg->sensorNumber);	

    pProt = new Protocol("Pletacka-IoT", pletackaName , "Compiled at " __DATE__ " " __TIME__, [](const std::string& cmd, rbjson::Object* pkt) {
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
			eeprom.write(EEPROM_SNUMBER_A, pCfg->sensorNumber);
			eeprom.commit();
			sendLog("Snum SAVE", "Num: " + String(pCfg->sensorNumber));
			Layout.numberSave.setText("SAVED");
			showId();
			Layout.rebootButton.setText("Rebooting now");
			Layout.stateText.setText("Rebooting now");
			delay(500);
			ESP.restart();

			
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
		// ESP_LOGW("X");
		if(pProt == nullptr)
		{
			ESP_LOGE(TAG, "Protocol not initialized!");
			return;
		}
		else
		{
			// ESP_LOGW("X", "Add:%d", pProt);
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


void Pletacka_UI::UIoffLeds()
{
	if(pCfg->debugOn)
	{
		Layout.finLed.setOn(false);
		Layout.stopLed.setOn(false);
	}
}

///////////////////////////DISPLAY/////////////////////////

void Pletacka_UI::displayInit()
{  
    tft.init();
    tft.fontHeight(2);
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(textColour);
}

void Pletacka_UI::showId()
{
    tft.fillCircle(12, 12,  12, TFT_ORANGE);
    tft.drawCentreString(String(pCfg->sensorNumber), 12, 5 , 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
}


void Pletacka_UI::showError(String msg, int colour, bool sendToApp)
{
    tft.fillRoundRect(0, tft.height() - 20,  tft.width(), 20, radius, colour);
    tft.drawString(msg, 5,tft.height()-17, 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
	sendLog(msg, "DISP: showError", sendToApp);
	
}

void Pletacka_UI::hideError()
{
    tft.fillRoundRect(0, tft.height() - 20,  tft.width(), 20, radius, bcgColour);
}


void Pletacka_UI::showMsg(String msg, bool sendToApp)
{
    
	tft.fillRoundRect(28, 0,  tft.width()-28, 24, radius, blockColour);
    tft.drawString(msg, 31, 5, 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
	sendLog(msg, "DISP: showMsg", sendToApp);
}

void Pletacka_UI::hideMsg()
{
    tft.fillRoundRect(28, 0,  tft.width()-28, 24, radius, blockColour);
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
    else if (status == "FINISHED")
    {
        bcgCol = TFT_ORANGE;
    }
    else
    {
        bcgCol = TFT_DARKGREEN;
    }


    tft.fillRoundRect(0, tft.height() - 30 - 30,  tft.width(), 30, radius, bcgCol);

    tft.setTextColor(TFT_WHITE);
    tft.drawCentreString(status, tft.width()/2, tft.height() - 30 - 25, 4);  //string,start x,start y, font weight {1;2;4;6;7;8}

	sendLog(status, "DISP: showStatus", sendToApp);
}

void Pletacka_UI::hideStatus()
{
	tft.fillRoundRect(0, tft.height() - 30 - 30,  tft.width(), 30, radius, TFT_BLACK);
}



void Pletacka_UI::updateInfo(String status, bool sendToApp)
{
	String  value;
	iName = "";


    if (status == "STOP")
    {
		iStartOfStopState = millis();
		iName = "Zastaveno";
		sendLog(String(iStartOfStopState), "iStartOfStopState");
		if(pCfg->debugOn)
		{
			Layout.stopLed.setOn(true);
		}

    }
    else if (status == "REWORK")
    {
		tStopAll += millis()-iStartOfStopState;
		
    }
	else if (status == "FINISHED")
	{
		cFinished++;
		
		if(pCfg->debugOn)
		{
			Layout.finLed.setOn(true);
		}
	}


	if(pCfg->debugOn)
	{
		Layout.stateText.setText(status.c_str());
	}	
	

	// debugln("Update -> iNam:"+iName+"; val:"+value+"sS:"+iStartOfStopState+"; tSn:"+tStopNow+"; tAa:"+tStopAll+"; cFin:"+cFinished);

	sendLog(status, "DISP: showInfo", sendToApp);
}

void Pletacka_UI::showInfo()
{
	static String value = "-";
	static String unit = "-";

	int Seconds = 0;
	int Minutes = 0;
	int Hours = 0;	

    if (iName == "Zastaveno")
    {
		iBgCol = TFT_RED;
		tStopNow = (millis()-iStartOfStopState)/1000;

		Seconds = tStopNow%60;
  		Minutes = (tStopNow/60)%60;
  		Hours = (tStopNow/3600)%24;

		if(Seconds<=60 && Minutes==0 && Hours == 0)
		{
			value = String(Seconds);
			unit = "s";
		}
		else if(Minutes<=60 && Hours == 0)
		{
			value = String(Minutes);
			unit = "m";
		}
		else
		{
			value = String(Hours);
			unit = "h";
		}

		

		String valueFull = String(String(Hours)+":"+String(Minutes)+":"+String(Seconds));


		if(pCfg->debugOn)
		{
			Layout.iZastavVal.setText(value.c_str());
			Layout.iZastavUnit.setText(unit.c_str());
			Layout.iZastavVal2.setText(valueFull.c_str());
		}	


    }
    else
    {
        iName ="Upleteno";
		iBgCol = TFT_DARKGREEN;
		value = String(int(cFinished/2));
		unit = "p";

		if(pCfg->debugOn)
		{
			Layout.iUplVal.setText(value.c_str());
			Layout.iUplUnit.setText(unit.c_str());
			Layout.iZastavVal.setText("-");
			Layout.iZastavUnit.setText("-");
			Layout.iZastavVal2.setText("-");
		}		
		
    }

	// debugln("iNam:"+iName+"; val:"+value+"; sS:"+iStartOfStopState+"; tSn:"+tStopNow+"; tAa:"+tStopAll+"; cFin:"+cFinished+"; Time:"+String(String(Hours)+":"+String(Minutes)+":"+String(Seconds)));

    // if(valueNew != )
	tft.fillRoundRect(0, 30,  tft.width(), 145, radius, iBgCol);

	// sprintf(text, "%")

	tft.setTextColor(TFT_WHITE);
	tft.drawCentreString(iName, tft.width()/2, 40, 4);  //string,start x,start y, font weight {1;2;4;6;7;8}
	tft.drawCentreString(value+" "+unit, tft.width()/2, 80, 6);  //string,start x,start y, font weight {1;2;4;6;7;8}
	// tft.drawCentreString(unit, tft.width()/2, 120, 4);  //string,start x,start y, font weight {1;2;4;6;7;8}
	// tft.drawCentreString(String(String(5)+" s"), tft.width()/2, 60, 4);  //string,start x,start y, font weight {1;2;4;6;7;8}
	// valueOld = valueNew;
	
	
}

void Pletacka_UI::hideInfo()
{
    tft.fillRoundRect(0, 30,  tft.width(), 145, radius, TFT_BLACK);
}


///////////////////////////SETTINGS/////////////////////////

void Pletacka_UI::changeID()
{
	char state = ' ';
	int time = 0;
	int oldID = pCfg->sensorNumber;
	showStatus("Change ID", false);
	delay(2000);
	while(state!='q')
	{
		switch (state)
		{
		case 'p':
			pCfg->sensorNumber++;
			showId();
			state = 'd';
			break;

		case 'm':
			pCfg->sensorNumber--;
			showId();
			state = 'd';
			break;

		case 'b':
			if(time == 0)
			{
				time = millis();
			}
			if((millis()-time)>3000)
			{
				time = 0;
				state = 'q';

				if(oldID != pCfg->sensorNumber)
				{
					eeprom.write(EEPROM_SNUMBER_A, pCfg->sensorNumber);
					eeprom.commit();
					print("Set new ID -> "+String(pCfg->sensorNumber), false);
					showStatus(String(pCfg->sensorNumber)+" new ID", false);						
				}
				else
				{
					print("Nothing to change-ID", false);
					showStatus("Nothing to change-ID", false);					
				}
			}
			break;
		
		default:
			if(!digitalRead(BTN_UP) && !digitalRead(BTN_DOWN))
			{
				state = 'b';
			}
			else if(!digitalRead(BTN_UP))
			{
				state = 'p';
			}
			else if (!digitalRead(BTN_DOWN))
			{
				state = 'm';
			}
			break;
		}
		delay(100);
	}
}


