#pragma once

#include <Arduino.h>
#include "pletacka_config.hpp"
#include "Pletacka_display.hpp"

class Board_tester
{
    private:
		Pletacka_display pletacka_display;

    public:
        void test();
   
};




