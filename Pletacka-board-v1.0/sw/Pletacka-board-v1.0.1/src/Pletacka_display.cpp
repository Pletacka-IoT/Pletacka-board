#include "Pletacka_display.hpp"

String tim(int time)
{
    if(time<10)
    {
        return "0" + String(time);
    }
    return String(time);
}

void Pletacka_display::displayInit(PletackaConfig* config)
{
    pletackaNumber = &(config->sensorNumber);
    
    tft.init();
    tft.fontHeight(2);
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(textColour);

    showId(*pletackaNumber);
}

void Pletacka_display::timeInit()
{
    if(WiFi.status() == WL_CONNECTED)
    {
        const char* ntpServer = "pool.ntp.org";
        const long  gmtOffset_sec = 3600;
        const int   daylightOffset_sec = 3600; 

        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);       
    }
    else
    {
        showError("Time ERROR");
        Serial.println("Time ERROR");
    }
    

}

void Pletacka_display::showId(int number)
{
    tft.fillCircle(12, 12,  12, TFT_DARKGREEN);
    tft.drawCentreString(String(number), 12, 5 , 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
}

void Pletacka_display::showTime()
{
    tft.fillRoundRect(30, 0,  70, 24, radius, blockColour);

    if(WiFi.status() == WL_CONNECTED)
    {
        getLocalTime(&tm);
        

        String time = tim(tm.tm_hour)+":"+tim(tm.tm_min)+":"+tim(tm.tm_sec);
        tft.drawString(time, 35, 5 , 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
        Serial.printf("Time: %d:%d:%d%\r", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    else
    {
        tft.drawString("ERROR", 35, 5 , 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
        Serial.println("Time ERROR");
    }

}

void Pletacka_display::showError(String msg, int colour )
{
    tft.fillRoundRect(0, tft.height()- 15,  tft.width(), 15, radius, colour);
    tft.drawString(msg, 5,tft.height()-12, 1);  //string,start x,start y, font weight {1;2;4;6;7;8}
    // int x = TFT_RED
}

void Pletacka_display::hideError()
{
    tft.fillRoundRect(0, tft.height()- 15,  tft.width(), 15, radius, bcgColour);
}



void Pletacka_display::showMsg(String msg)
{
    tft.fillRoundRect(105, 0,  135, 24, radius, blockColour);
    tft.drawString(msg, 110, 5, 2);  //string,start x,start y, font weight {1;2;4;6;7;8}
}

void Pletacka_display::hideMsg()
{
    tft.fillRoundRect(105, 0,  135, 24, radius, blockColour);
}

void Pletacka_display::showStatus(String status)
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

void Pletacka_display::hideStatus()
{
    tft.fillRoundRect(40, 50,  160, 45, radius, TFT_BLACK);
}

// void Pletacka_display::showSend()
// {
//     int x = 200;
//     int y = 72;
//     int r = 20;

//     tft.fillCircle(x, y, r, TFT_RED);
//     tft.drawLine(x-15, y, x+15, y, TFT_WHITE);
//     tft.drawLine(x+15, y, x+5, y-8, TFT_WHITE);
//     tft.drawLine(x+15, y, x+5, y+8, TFT_WHITE);
    
// }

// void Pletacka_display::hideSend()
// {
//     int x = 200;
//     int y = 72;
//     int r = 20;

//     tft.fillCircle(x, y, r, TFT_BLACK);

    
// }




void Pletacka_display::showStatusX(String status, int x)
{
    // tft.setTextColor(TFT_WHITE);
    // tft.fillRoundRect(40, 50,  160, 45, radius, TFT_DARKGREEN);
    // tft.drawCentreString(status, 120, 56, x);  //string,start x,start y, font weight {1;2;4;6;7;8}


}
