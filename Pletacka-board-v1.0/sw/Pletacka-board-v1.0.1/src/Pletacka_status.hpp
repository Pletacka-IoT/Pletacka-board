#pragma once

#include <Arduino.h>
#include "Pletacka_config.hpp"
#include "Optocoupler.hpp"

class Pletacka_status
{
private:
    
    Optocoupler optoStop; 
	Optocoupler optoFinish; 
    

    struct Optocuplrs
    {
        bool stop;
        bool finish;
    }opto;


    enum states
    {
        SSTOP = 1,
        SFINISHED = 0,
    };

    enum pletac_run
    {
        DEF = -1,
        ON = 0,
        STOP = 1, 
        FINISHED = 2,
    };    


    
    

public:

    void init(PletackaConfig* config);
    String getStatus();
    
};




