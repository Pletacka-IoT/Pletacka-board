#include "Pletacka_status.hpp"


void Pletacka_status::init(PletackaConfig* config, Pletacka_UI* inUI)
{
	// cfg = config;
	UI = inUI;

	optoFinish.setPin(OP_1_FINISH);
	optoStop.setPin(OP_2_STOP);

	opto.finish = !optoFinish.state();  //Change
	opto.stop = optoStop.state();

}

/**
 * @brief Get pletacka status
 * 
 * @return String state
 */
String Pletacka_status::getStatus()
{
	ESP_LOGD("GES", "GES");
	
	static int Spletac1_run = ON;

	String output = "";
	
	opto.finish = optoFinish.state();	//Change
	opto.stop = optoStop.state();

	switch (Spletac1_run)
	{
		case ON:
			// pletacka.debugln("xON");
			Spletac1_run = DEF;
			output = "";
			break;
		case STOP:
			// pletacka.debugln("xSTOP");
			output = "STOP";

			if (opto.stop!=SSTOP) //END STOP
			{
				// pletacka.debugln("xREWORK");
				Spletac1_run = DEF;
				output = "REWORK";
			}
			break;
		
		default:
			// pletacka.debugln("xDEF");

			if(opto.stop==SSTOP)
			{
				Spletac1_run = STOP;
			}
			else
			{
				if(opto.finish==SFINISHED)
				{
					output = "FINISHED";
				}
				else
				{
					output = "";
				}				
			}
			break;
	}
	// UI->debugln("Status: " + output);
	Serial.println("GES:"+output);
	ESP_LOGD("GES2", "GES2");
	return output;    


}