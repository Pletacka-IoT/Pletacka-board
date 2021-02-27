#pragma once

#define STATIC_IP true


const int LED_SEND = 27;
const int OP_1_FINISH = 36;
const int OP_2_STOP = 37;
const int BTN_UP = 0;
const int BTN_DOWN = 35;
const int PWR_VOLTAGE = 32;
const int GPIO_25 = 25;
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
	bool debugOn;	//Startup into debug mode - Serial Debug
	String udpIP;
	int udpPort;

};

