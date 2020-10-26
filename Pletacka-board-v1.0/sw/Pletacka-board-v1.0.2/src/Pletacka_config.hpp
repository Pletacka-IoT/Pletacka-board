#pragma once

const int LED_SEND  = 27;
const int LED_WIFI = 26;
const int LED_ON = 25;
const int OP_1_FINISH = 39;
const int OP_2_STOP = 38;
const int OP_3 = 37;
const int OP_4 = 36;
const int BTN_ENTER = 21;
const int BTN_B1 = 12;
const int BTN_UP = 0;
const int BTN_DOWN = 35;
const int TMP_SDA = 22;
const int TMP_SCL = 17;
const int TMP_OS = 2;
const int PWR_VOLTAGE = 32;
const int GPIO_13 = 13;
const int GPIO_15 = 15;
const int GPIO_33 = 33;

const int EEPROM_SIZE = 50;
const int EEPROM_SNUMBER_A = 5;

struct PletackaConfig
{
	PletackaConfig()
		: sensorNumber(1)
		, serverUrl("")
		, serverUrlBackup("")
		, wifiName("")
		, wifiPassword("")
		, wifiChenel(1)
		, wifiDefaulAp(false)
		, apName("")
		, apPassword("")
		, apChanel(1) 
		, debugOn(false)
		, udpIP("192.168.0.112")
		, udpPort(2727)

		{

	}

	int sensorNumber;   //Sensor number
	String serverUrl; 	//Server URL address
	String serverUrlBackup; 	//Server URL address
	String wifiName;    //WiFi name
	String wifiPassword;//WiFi password
	int wifiChenel;     //WiFi chanel
	bool wifiDefaulAp;  //Run AP on startup
	String apName;      //AP name
	String apPassword;  //AP password
	int apChanel;       //AP chanel
	bool debugOn;	//Startup into debug mode - Serial Debug
	String udpIP;
	int udpPort;

};

