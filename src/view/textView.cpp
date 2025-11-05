#include "textView.hpp"
#include <iomanip>
#include <iostream>
using namespace std;

TextView::TextView(CPUModel& m):model(m){ model.attach(this); }

void TextView::update()
{
    cout<<"==== Cycle "<<model.cycles<<" ====\n";
    cout<<"PC=0x"<<hex<<setw(8)<<setfill('0')<<model.PC<<dec<<"\n";
    cout<<"--- Registers ---\n"<<model.registerSnapshot();
    cout<<"--- Memory ---\n"<<model.memorySnippet(0,4);
    cout<<"Cycles:"<<model.cycles<<" MemR:"<<model.memReads<<" MemW:"<<model.memWrites<<"\n";
    cout<<"ALU ops:\n";
    for(auto&p:model.getALU().stats()) cout<<"  "<<p.first<<": "<<p.second<<"\n";
    cout<<"Instr counts:\n";
    for(auto&p:model.instrCounts) cout<<"  "<<p.first<<": "<<p.second<<"\n";
    cout<<"====================\n";
}
