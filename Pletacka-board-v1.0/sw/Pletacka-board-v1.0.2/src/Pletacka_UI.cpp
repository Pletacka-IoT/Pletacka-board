#include "Pletacka_UI.hpp"



void Pletacka_UI::init(PletackaConfig* inCfg, rb::Protocol* inProt)
{
    pCfg = inCfg;
	pProt = inProt;


	displayInit();
	showId(pCfg->sensorNumber);

	

}

void Pletacka_UI::displayInit()
{  
    tft.init();
    tft.fontHeight(2);
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(textColour);
}


void Pletacka_UI::showId(int number)
{
    tft.fillCircle(12, 12,  12, TFT_DARKGREEN);
    tft.drawCentreString(String(number), 12, 5 , 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
}


void Pletacka_UI::showError(String msg, int colour )
{
    tft.fillRoundRect(0, tft.height()- 15,  tft.width(), 15, radius, colour);
    tft.drawString(msg, 5,tft.height()-12, 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
}

void Pletacka_UI::hideError()
{
    tft.fillRoundRect(0, tft.height()- 15,  tft.width(), 15, radius, bcgColour);
}


void Pletacka_UI::showMsg(String msg)
{
    tft.fillRoundRect(105, 0,  135, 24, radius, blockColour);
    tft.drawString(msg, 110, 5, 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
}

void Pletacka_UI::hideMsg()
{
    tft.fillRoundRect(105, 0,  135, 24, radius, blockColour);
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


    tft.fillRoundRect(40, 50,  160, 45, radius, bcgCol);

    tft.setTextColor(TFT_WHITE);
    tft.drawCentreString(status, 120, 62, 4);  //string,start x,start y, font weight {1;2;4;6;7;8}


}

void Pletacka_UI::hideStatus()
{
    tft.fillRoundRect(40, 50,  160, 45, radius, TFT_BLACK);
}

void Pletacka_UI::sendLog(String text)
{

}

void Pletacka_UI::test()
{
	pProt->send_log("LOG");
}