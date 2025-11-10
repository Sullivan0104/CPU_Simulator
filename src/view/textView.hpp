#pragma once
#include "../model/subject.hpp"
#include "../model/cpuModel.hpp"
#include <iostream>

class TextView : public Observer 
{
public:
    explicit TextView(CPUModel& model);
    void update() override;

private:
    CPUModel& model;
    
};
