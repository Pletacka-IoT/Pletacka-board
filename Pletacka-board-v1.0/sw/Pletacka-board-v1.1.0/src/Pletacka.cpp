#include "Pletacka.hpp"

#define STOP_CODE ESP_LOGW("STOP_CODE", "STOP_CODE"); while(1){;}



Pletacka::Pletacka()
{
}

Pletacka::~Pletacka()
{
}

void Pletacka::config(PletackaConfig* config, Protocol* inProt )
{
	pCfg = config;
	pProt = inProt;

	Serial.begin(115200);		

	pinMode(LED_SEND, OUTPUT);
	pinMode(LED_WIFI, OUTPUT);
	pinMode(LED_ON, OUTPUT);
	
	pinMode(BTN_ENTER, INPUT);
	pinMode(BTN_B1, INPUT);
	pinMode(BTN_UP, INPUT);
	pinMode(BTN_DOWN, INPUT);

	pinMode(PWR_VOLTAGE, INPUT);

	digitalWrite(LED_ON, true);


	UI.init(pCfg);

	if(!digitalRead(BTN_DOWN))
	{
		UI.changeID();
	}


	pletacka_wifi.init(pCfg, &UI);

	UI.initUIGrid(pProt);


	if(pCfg->debugOn || !digitalRead(BTN_DOWN))
	{
		Serial.println("Debug");
		pCfg->debugOn = true;
		UI.showError("DEBUG MODE", TFT_ORANGE);
		// UI.showError(WiFi., TFT_ORANGE);

	}

	// UI.debug("Debaguju");
	// UI.println("Seriuju");
	
	

	pletacka_status.init(pCfg, &UI);
	pletacka_alive.init(pCfg, &UI);



	apiState.setServerName(pCfg->serverUrl + "/" + pCfg->sensorNumber);
	apiStateBackup.setServerName(pCfg->serverUrlBackup + "/" + pCfg->sensorNumber);
	UI.println("Server:" + apiState.getServerName());




	UI.println("Sensor number " + String(pCfg->sensorNumber) + " is configured");
	
	
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
	static int errorCounter = 0;
	counter++;

	if(errorCounter>2)
	{
		UI.showMsg("Send Err Reboot");
		delay(2000);
		ESP.restart();
	}

	auto request = apiState.GetReqest(state);

	Serial.println("\nGET\n  Req:" + request.request + "\n  Code : "+String(request.code)+" ->\""+String(request.main) + "\"");

	if(request.code == 200)
	{
		UI.showMsg(String(counter) + "[" + state[0] + state[1] + "]" + " -> OK");
		UI.hideError();
	}
	else
	{
		auto requestBackup = apiStateBackup.GetReqest(state);

		Serial.println("\nGET\n  Req:" + requestBackup.request + "\n  Code : "+String(requestBackup.code)+" ->\""+String(requestBackup.main) + "\"");

		if(requestBackup.code == 200)
		{
			UI.showMsg(String(counter) + "[" + state + "]" + " -> OK");
			UI.hideError();
		}
		else
		{
			UI.showError(requestBackup.code + "->"+ requestBackup.main);
			UI.hideMsg();
			errorCounter++;
		}
	}

	
}

void Pletacka::sendAlive(int sensorNumber)
{
	pletacka_alive.sendAlive(sensorNumber);
}


void Pletacka::buttonPush()
{

	if(!digitalRead(BTN_DOWN))
	{
		UI.showMsg("Reboot...");
		delay(2000);
		ESP.restart();
	}
	

}



// void Pletacka::editSensorNumber()
// {
// 	int actualNumber = pCfg->sensorNumber;
	
// 	UI.showMsg("Setup s. number", false);

// 	while(!digitalRead(BTN_ENTER))
// 	{

// 		if(!digitalRead(BTN_UP))
// 		{
// 			pCfg->sensorNumber++;
// 			UI.showId(pCfg->sensorNumber);
// 		}
// 		else if (!digitalRead(BTN_DOWN))
// 		{
// 			pCfg->sensorNumber--;
// 			UI.showId(pCfg->sensorNumber);
// 		}

// 		delay(300);
// 	}

// 	if(actualNumber != pCfg->sensorNumber)
// 	{
// 		pletacka_eeprom.write(EEPROM_SNUMBER_A, pCfg->sensorNumber);
// 		pletacka_eeprom.commit();
// 		UI.showError("OK", TFT_GREEN);
// 	}
// 	else
// 	{
// 		UI.showError("Nothing to change", TFT_ORANGE);
// 	}
// }
