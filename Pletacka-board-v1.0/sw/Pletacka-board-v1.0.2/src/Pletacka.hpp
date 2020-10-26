# pragma once

#include <Arduino.h>

#include "NetteApi.hpp"
#include "Pletacka_config.hpp"
// #include "Pletacka_display.hpp"
#include "Pletacka_UI.hpp"
#include "Pletacka_wifi.hpp"
#include "Pletacka_debug.hpp"
#include "Pletacka_status.hpp"
#include "Pletacka_alive.hpp"

#include "EEPROM.h"

#include "gridui.h"
#include "rbprotocol.h"
#include "rbwebserver.h"
#include "rbwifi.h"

using namespace rb;
using namespace gridui;

#define ADC_EN          14
#define ADC_PIN         34
#define BUTTON_1        35
#define BUTTON_2        0 

class Pletacka
{
private:
	Pletacka_UI ui;

	// Pletacka_display pletacka_display;
	PletackaConfig* cfg = NULL;
	Pletacka_wifi pletacka_wifi;
	Pletacka_debug pletacka_debug;
	Pletacka_status pletacka_status;
	Pletacka_alive pletacka_alive;
	EEPROMClass pletacka_eeprom;
	NetteApi apiState;
	NetteApi apiStateBackup;


	Protocol* gProt = nullptr;



public:
	Pletacka();
	~Pletacka();
	void config(PletackaConfig* config, Protocol *gPro);

	String isChange();
	void sendState(String state);
	void sendAlive(int sensorNumber);
	int editSensorNumber(int actualNumber);

	void debug(String message, String prefix = "D:");
	void debugln(String message, String prefix = "D:");
	void print(String message, String prefix = "P:");
	void println(String message, String prefix = "P:");
	
};



