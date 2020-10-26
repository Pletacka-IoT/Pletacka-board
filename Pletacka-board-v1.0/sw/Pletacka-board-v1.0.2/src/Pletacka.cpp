#include "Pletacka.hpp"

#define STOP_CODE ESP_LOGW("STOP_CODE", "STOP_CODE"); while(1){;}



Pletacka::Pletacka()
{
}

Pletacka::~Pletacka()
{
}

void Pletacka::config(PletackaConfig* config, Protocol* gPro )
{
	cfg = config;
	gProt = gPro;

	Serial.begin(115200);	

	pletacka_eeprom.begin(50);
	if(pletacka_eeprom.read(EEPROM_SNUMBER_A) == 255)
	{
		pletacka_eeprom.write(EEPROM_SNUMBER_A, 1);
		pletacka_eeprom.commit();
	}
	cfg->sensorNumber = pletacka_eeprom.read(EEPROM_SNUMBER_A);	

	pinMode(LED_SEND, OUTPUT);
	pinMode(LED_WIFI, OUTPUT);
	pinMode(LED_ON, OUTPUT);
	
	pinMode(BTN_ENTER, INPUT);
	pinMode(BTN_B1, INPUT);
	pinMode(BTN_UP, INPUT);
	pinMode(BTN_DOWN, INPUT);

	pinMode(PWR_VOLTAGE, INPUT);

	digitalWrite(LED_ON, true);



	if(!digitalRead(BTN_ENTER))
	{
		cfg->sensorNumber = editSensorNumber(cfg->sensorNumber);
		// UI.hideMsg();
	}
	UI.init(cfg);

	pletacka_wifi.init(cfg, &UI);

	UI.initUIGrid(gProt);

	


	if(cfg->debugOn || !digitalRead(BTN_DOWN))
	{
		Serial.println("Debug");
		cfg->debugOn = true;
		UI.showError("DEBUG MODE", TFT_ORANGE);
	}

	UI.debugln("Debaguju");
	UI.println("Seriuju");
	
	

	pletacka_status.init(cfg, &UI);
	pletacka_alive.init(cfg, &UI);



	apiState.setServerName(cfg->serverUrl + "/" + cfg->sensorNumber);
	apiStateBackup.setServerName(cfg->serverUrlBackup + "/" + cfg->sensorNumber);
	UI.println("Server:" + apiState.getServerName());




	UI.println("Sensor number " + String(cfg->sensorNumber) + " is configured");
	
	
}

/**
 * @brief Is pletacka status changed
 * 
 * @return String status or false
 */
String Pletacka::isChange()
{
	static String lastStatus = "";
	String nowStatus = pletacka_status.getStatus();

	// Serial.println("NowS:"+nowStatus);

	if(nowStatus != lastStatus)
	{
		lastStatus = nowStatus;
		return nowStatus;
	}

	return "";
}

void Pletacka::sendState(String state)
{
	static int counter = 0;
	counter++;

	auto request = apiState.GetReqest(state);

	Serial.println("\nGET\n  Req:" + request.request + "\n  Code : "+String(request.code)+" ->\""+String(request.main) + "\"");

	if(request.code == 200)
	{
		UI.showMsg(String(counter) + " -> OK");
		UI.hideError();
	}
	else
	{
		auto requestBackup = apiStateBackup.GetReqest(state);

		Serial.println("\nGET\n  Req:" + requestBackup.request + "\n  Code : "+String(requestBackup.code)+" ->\""+String(requestBackup.main) + "\"");

		if(requestBackup.code == 200)
		{
			UI.showMsg("Bac-"+String(counter) + " -> OK");
			UI.hideError();
		}
		else
		{
			UI.showError(requestBackup.code + "->"+ requestBackup.main);
			UI.hideMsg();
		}
	}
	
}

void Pletacka::sendAlive(int sensorNumber)
{
	pletacka_alive.sendAlive(sensorNumber);
}



int Pletacka::editSensorNumber(int actualNumber)
{
	int newNumber = actualNumber;
	UI.showMsg("Setup s. number");

	while(!digitalRead(BTN_ENTER))
	{

		if(!digitalRead(BTN_UP))
		{
			newNumber++;
			UI.showId(newNumber);
		}
		else if (!digitalRead(BTN_DOWN))
		{
			newNumber--;
			UI.showId(newNumber);
		}

		delay(300);
	}

	if(actualNumber != newNumber)
	{
		pletacka_eeprom.write(EEPROM_SNUMBER_A, newNumber);
		pletacka_eeprom.commit();
		UI.showError("OK", TFT_GREEN);
	}
	else
	{
		UI.showError("Nothing to change", TFT_ORANGE);
	}

	return newNumber;
}
