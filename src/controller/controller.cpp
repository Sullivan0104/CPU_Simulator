#include "controller.hpp"
#include <iostream>
using namespace std;

Controller::Controller(CPUModel& m,bool step):model(m),stepMode(step){}

void Controller::run()
{
    while(!model.halted())
    {
        if(!model.step()) break;
        if(stepMode)
        {
            cout<<"Press Enter for next instruction (q to quit)\n";
            string s; getline(cin,s);
            if(!s.empty()&&(s[0]=='q'||s[0]=='Q')) break;
        }
    }
    cout<<"Simulation ended. Cycles="<<model.cycles<<"\n";
}
