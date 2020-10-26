#include "Pletacka_UI.hpp"



void Pletacka_UI::init(PletackaConfig* config, TFT_eSPI* inDp, Protocol* gProtocol)
{
    cfg = config;
	gProt = gProtocol;
    dp = inDp;

	displayInit();

	// gProt->send_log("Ahoj");
	ESP_LOGE("E");


	showId(cfg->sensorNumber);
	ESP_LOGE("E");

	dp->fillRoundRect(0, dp->height()- 15,  dp->width(), 15, radius, TFT_BLUE);
	ESP_LOGE("E");
	// dp->drawString("ASD", 5,dp->height()-12, 1);  //string,start x,start y, font weight {1;2;4;6;7;8}
	dp->print("ASD");
	ESP_LOGE("E");

	delay(3000);
	
	showError("Error");
	ESP_LOGE("E");

	delay(100000);
}

void Pletacka_UI::displayInit()
{  
    dp->init();
    dp->fontHeight(2);
    dp->setRotation(3);
    dp->fillScreen(TFT_BLACK);
    dp->setTextColor(textColour);
}


void Pletacka_UI::showId(int number)
{
    dp->fillCircle(12, 12,  12, TFT_DARKGREEN);
    dp->drawCentreString(String(number), 12, 5 , 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
}


void Pletacka_UI::showError(String msg, int colour )
{
    dp->fillRoundRect(0, dp->height()- 15,  dp->width(), 15, radius, colour);
    dp->drawString(msg, 5,dp->height()-12, 1);  //string,start x,start y, font weight {1;2;4;6;7;8}
}

void Pletacka_UI::hideError()
{
    dp->fillRoundRect(0, dp->height()- 15,  dp->width(), 15, radius, bcgColour);
}


void Pletacka_UI::showMsg(String msg)
{
    dp->fillRoundRect(105, 0,  135, 24, radius, blockColour);
    dp->drawString(msg, 110, 5, 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
}

void Pletacka_UI::hideMsg()
{
    dp->fillRoundRect(105, 0,  135, 24, radius, blockColour);
}

void Pletacka_UI::showStatus(String status)
{
    int bcgCol;

    if(status == "ON")
    {
        bcgCol = TFT_BLUE;
    }
    else if (status == "STOP")
    {
        bcgCol = TFT_RED;
    }
    else if (status == "REWORK")
    {
        bcgCol = TFT_YELLOW;
    }
    else
    {
        bcgCol = TFT_DARKGREEN;
    }


    dp->fillRoundRect(40, 50,  160, 45, radius, bcgCol);

    dp->setTextColor(TFT_WHITE);
    dp->drawCentreString(status, 120, 62, 4);  //string,start x,start y, font weight {1;2;4;6;7;8}


}

void Pletacka_UI::hideStatus()
{
    dp->fillRoundRect(40, 50,  160, 45, radius, TFT_BLACK);
}

void Pletacka_UI::sendLog(String text)
{

}