#include "Pletacka_wifi.hpp"

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

void Pletacka_wifi::init(PletackaConfig* config, Pletacka_UI* inUI)
{
	UI = inUI;
	cfg = config;

	connectWifi();
}




void Pletacka_wifi::connectWifi()
{
	Serial.println("Connecting to " + cfg->wifiName);



	if(true)
	{
		// From : https://randomnerdtutorials.com/esp32-static-fixed-ip-address-arduino-ide/
		// Set your Static IP address
		IPAddress local_IP(192, 168, 0, 200+cfg->sensorNumber);
		// Set your Gateway IP address
		IPAddress gateway(192, 168, 0, 1);

		IPAddress subnet(255, 255, 255, 0);
		IPAddress primaryDNS(10, 255, 255, 10);   //optional
		IPAddress secondaryDNS(8, 8, 4, 4); //optional

		// Configures static IP address
		if (!pWiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
			UI->showError("STA Failed to configure", TFT_RED, false);
		}		
		
	}
	UI->showMsg("Connecting " + cfg->wifiName, false); 

	pWiFi.begin(cfg->wifiName.c_str(), cfg->wifiPassword.c_str());

	int counter = 0;
	bool ledWifiState = true;

	while (pWiFi.status() != WL_CONNECTED) {
			counter++;
			delay(500);
			Serial.print(".");
			
			digitalWrite(LED_WIFI, ledWifiState);
			ledWifiState = !ledWifiState;

			if(counter> 10)
			{
					UI->showError("Not connected to pWiFi", TFT_RED, false);            
			}
	}

	
	UI->showMsg("WiFi " + cfg->wifiName, false);
	UI->hideError();

	Serial.println("\nWiFi connected");
	Serial.print("IP address: ");
	Serial.print(pWiFi.localIP().toString());
	Serial.print("    MAC address: ");
	Serial.println(String(pWiFi.macAddress()));   
	digitalWrite(LED_WIFI, true); 
		
}



