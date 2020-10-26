/**
 * @file main.cpp
 * @author Jakub Andrýsek (email@kubaandrysek.cz)
 * @brief 
 * @version 0.1
 * @date 2020-08-14
 * 
 * @copyright Copyright (c) 2020 Jakub Andrýsek
 * 
 * @link https://kubaandrysek.cz
 */

#include <Arduino.h>
#include "Pletacka.hpp"
#include "BasicOTA.hpp"
#include <SPI.h>
#include "WiFi.h"
#include "ArduinoMetronome.hpp"
#include "Board_tester.hpp"

#define STATIC_IP true


static rb::Protocol* gProt = nullptr;

void mainProgram()
{
	//Main setup

	// Uncoment for testing 
	// Board_tester tester;
	// tester.test();

	// BasicOTA ota;
	Pletacka pletacka;
	PletackaConfig config;
	WiFiClass pWiFi;
	ArduinoMetronome statusMetronome(10);
	ArduinoMetronome customMetronome(1000);
	ArduinoMetronome wifiTester(500);
	ArduinoMetronome aliveMetronome(10000);

	
	config.serverUrl = "http://192.168.0.2/api/v1/thisSensor/add-event";
	config.serverUrlBackup = "http://192.168.0.2/Backup/api/v1/thisSensor/add-event";
	// config.wifiName = "Pletacka-IoT";
	// config.wifiPassword = "PletackaPlete";
	// config.wifiName = "WLOffice";
	// config.wifiPassword = "$BlueC6r&R06D";	
	config.wifiName = "Suzand";
	config.wifiPassword = "Pucini.13";
	// config.wifiName = "Technika";
	// config.wifiPassword = "materidouska";
	config.wifiDefaulAp = false;
	config.apName = "AP-Pletacka-" + config.sensorNumber;
	config.apPassword = "PletackaPlete";
	config.udpIP = "192.168.0.2";
	config.udpPort = 2727;
	config.debugOn = true;

	
	pletacka.config(&config, gProt);

	pletacka.ui()->println("Funguje");





	statusMetronome.startupDelayMs(15000);
	aliveMetronome.startupDelayMs(1000);
	wifiTester.startupDelayMs(3000);


	
	// ota.begin();
	
	
	pletacka.ui()->println("println");
	pletacka.ui()->debugln("debugln");


	int ledSend = 0;
	bool ledWifiState = false;
	int startAlive = 0;


	//Main loop
	while (true)
	{
		// ota.handle();

		
		//	Status loop
		if(statusMetronome.loopMs())
		{
			
			String status = "";
			if((status = pletacka.isChange())!= "")
			{
				ledSend = millis();
				digitalWrite(LED_SEND, true);
				pletacka.ui()->println("Status: " + status);
				pletacka.ui()->showStatus(status);
				pletacka.sendState(status);
				
			}

			if(millis()-ledSend > 700)
			{
				digitalWrite(LED_SEND, false);
			}

			
		}

		//	Send alive loop
		if(aliveMetronome.loopMs())
		{			
			startAlive = millis();
			pletacka.sendAlive(config.sensorNumber);
			digitalWrite(LED_ON, true);
		}


		if(millis()-startAlive > 800)
		{
			digitalWrite(LED_ON, false);
		}
		
		//	WiFi connection test loop
		if(wifiTester.loopMs())
		{			
			if(pWiFi.status() != WL_CONNECTED)
			{
				digitalWrite(LED_WIFI, ledWifiState);
				ledWifiState = !ledWifiState;
				pletacka.ui()->showError("Not connected to WiFi"); 
				pletacka.ui()->showMsg("WiFi ERROR");
				delay(2000);
				pletacka.ui()->showStatus("RESTART...");
				delay(3000);
				ESP.restart(); 
			}
		}



		//	 Custom loop
		if(customMetronome.loopMs())
		{			
			// Serial.println("START: " + String(start));
		}		
		
	}
	
	
	
}



void setup() {
	mainProgram();
}





void loop() {}