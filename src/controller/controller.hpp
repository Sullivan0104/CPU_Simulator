#pragma once
#include "../model/cpuModel.hpp"

class Controller 
{
public:
    Controller(CPUModel& m,bool step=false);
    void run();
private:
    CPUModel& model;
    bool stepMode;
};
