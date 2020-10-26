#include "Board_tester.hpp"
#include "Pletacka.hpp"
#include "Optocoupler.hpp"


void Board_tester::test(PletackaConfig* cfg, rb::Protocol *pPro)
{
    
	

	WiFi::connect(cfg->wifiName.c_str(), cfg->wifiPassword.c_str());
	
	UI.init(cfg, pPro);
	
	UI.showMsg("Start testing");

    pinMode(LED_SEND, OUTPUT);
    pinMode(LED_WIFI, OUTPUT);
    pinMode(LED_ON, OUTPUT);
    
    pinMode(BTN_ENTER, INPUT);
    pinMode(BTN_B1, INPUT);
    pinMode(BTN_UP, INPUT);
    pinMode(BTN_DOWN, INPUT);

    pinMode(PWR_VOLTAGE, INPUT);

    Optocoupler opt_F(OP_1_FINISH);
    Optocoupler opt_S(OP_2_STOP);    
    Optocoupler opt_3(OP_3);    
    Optocoupler opt_4(OP_4); 

    // pinMode(38, INPUT);

    delay(1500);  


    UI.showMsg("LEDS");

    digitalWrite(LED_SEND, true);
    delay(300);
    digitalWrite(LED_SEND, false);
    delay(300);

    digitalWrite(LED_WIFI, true);
    delay(300);
    digitalWrite(LED_WIFI, false);
    delay(300);

    digitalWrite(LED_ON, true);
    delay(300);
    digitalWrite(LED_ON, false);
    delay(300);


    UI.showMsg("Press button:");

    UI.showStatus("ENTER");
    while(digitalRead(BTN_ENTER)){}
    delay(500);
    
    UI.showStatus("UP");
    while(digitalRead(BTN_UP)){}
    delay(500);
    
    UI.showStatus("DOWN");
    while(digitalRead(BTN_DOWN)){}
    delay(500);

    UI.showStatus("OK");
    delay(500);





    UI.showMsg("Optocoupler:");

    
    UI.showStatus("OP-1 FINISH");
    while(!opt_F.state()){}
    delay(500);

    UI.showStatus("OP-2 STOP");
    while(!opt_S.state()){}
    delay(500);

    UI.showStatus("OP-3");
    while(!opt_3.state()){}
    delay(500);

    UI.showStatus("OP-4 STOP");
    while(!opt_4.state()){}
    delay(500);

    UI.showStatus("OK");
    delay(500);

    

    // UI.showStatus("B1");
    // while(digitalRead(BTN_B1)){} //ERROR
    // delay(200);

    
    
    




	UI.showStatus("Test end");

    while (1)
	{
		;
	}
	
}
