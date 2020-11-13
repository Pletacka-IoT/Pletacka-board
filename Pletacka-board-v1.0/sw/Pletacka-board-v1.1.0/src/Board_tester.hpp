#pragma once

#include <Arduino.h>
#include "rbprotocol.h"
#include "Pletacka_UI.hpp"
#include "pletacka_config.hpp"

using namespace rb;

class Board_tester
{
    private:
		Pletacka_UI UI;
		// Protocol* pProt = nullptr;

    public:
        void test(PletackaConfig* cfg, rb::Protocol *pPro);
   
};




