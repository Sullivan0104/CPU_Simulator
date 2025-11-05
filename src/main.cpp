#include <iostream>
#include "model/cpuModel.hpp"
#include "view/textView.hpp"
#include "controller/controller.hpp"

int main(int argc,char**argv)
{
    if(argc<3)
    {
        std::cerr<<"Usage: "<<argv[0]<<" <memory_image.dat> <run|step>\n";
        return 1;
    }

    std::string file=argv[1];
    std::string mode=argv[2];
    bool step=(mode=="step");

    CPUModel cpu;
    if(!cpu.loadMemoryImage(file))
    {
        std::cerr<<"Cannot open "<<file<<"\n"; return 1;
    }

    TextView view(cpu);
    Controller ctrl(cpu,step);
    ctrl.run();
    return 0;
}
