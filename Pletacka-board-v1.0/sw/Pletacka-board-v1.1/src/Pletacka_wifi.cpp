#include "Pletacka_wifi.hpp"
#include "Pletacka.hpp"

/**
 * @brief Construct a new Pletacka_wifi::Pletacka_wifi object
 * 
 */
Pletacka_wifi::Pletacka_wifi()
{
 
}

Pletacka_wifi::~Pletacka_wifi()
{
}

void Pletacka_wifi::init(PletackaConfig* config)
{
	wifiCfg.wifiName = config->wifiName;
	wifiCfg.wifiPassword = config->wifiPassword;
	wifiCfg.wifiChanel = config->wifiChenel;
	wifiCfg.wifiDefaulAp = config->wifiDefaulAp;
	wifiCfg.apName = config->apName;
	wifiCfg.apPassword = config->apPassword;
	sensorNumber = config->sensorNumber;

	configConnection();
}

void Pletacka_wifi::configConnection()
{
	if(wifiCfg.wifiDefaulAp)
	{
		startAP();
			
	}
	else
	{
		connectWifi();
			
	}
		
}


void Pletacka_wifi::connectWifi()
{
	Serial.println("Connecting to " + wifiCfg.wifiName);


	// From : https://randomnerdtutorials.com/esp32-static-fixed-ip-address-arduino-ide/
		// Set your Static IP address
		IPAddress local_IP(192, 168, 0, 150+sensorNumber);
		// Set your Gateway IP address
		IPAddress gateway(192, 168, 0, 1);

		IPAddress subnet(255, 255, 255, 252);
		IPAddress primaryDNS(10, 255, 255, 10);   //optional
		IPAddress secondaryDNS(8, 8, 4, 4); //optional

		// Configures static IP address
		if (!plWiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
			// Serial.showError("STA Failed to configure");
		}		

	//End from

	plWiFi.begin(wifiCfg.wifiName.c_str(), wifiCfg.wifiPassword.c_str());

	int counter = 0;
	bool ledWifiState = true;

	while (plWiFi.status() != WL_CONNECTED) {
			counter++;
			delay(500);
			Serial.print(".");
			// Serial.showMsg("Connecting " + wifiCfg.wifiName); 
			digitalWrite(LED_WIFI, ledWifiState);
			ledWifiState = !ledWifiState;

			if(counter> 10)
			{
					// Serial.showError("Not connected to WiFi");            
			}
	}

	
	// Serial.showMsg("WiFi " + wifiCfg.wifiName);
	// Serial.hideError();

	Serial.println("\nWiFi connected");
	Serial.print("IP address: ");
	Serial.print(plWiFi.localIP().toString());
	Serial.print("    MAC address: ");
	Serial.println(String(plWiFi.macAddress()));   
	digitalWrite(LED_WIFI, true); 
	
		
}

void Pletacka_wifi::startAP()
{
		// Serial.showMsg("AP: "+wifiCfg.apName);
		Serial.println("Starting **" + wifiCfg.apName + "** AP");
		plWiFi.softAP(wifiCfg.apName.c_str(), wifiCfg.apPassword.c_str(), wifiCfg.apChanel );

}



