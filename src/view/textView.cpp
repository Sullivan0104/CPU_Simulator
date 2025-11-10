#include "textView.hpp"
#include <iomanip>
#include <iostream>
using namespace std;

TextView::TextView(CPUModel& m):model(m){ model.attach(this); }

void TextView::update()
{
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"; 
    cout<<"┃\t\t\tCycle "<<model.cycles<<"\n";
    cout << "┃\n"; 
    cout<<"┃  PC = 0x"<<hex<<setw(5)<<setfill('0')<<model.PC<<dec<<"\n";
    cout << "┣──────────────────────────────────────────────────────────\n"; 
    cout<<"┃\t\t\tRegisters\n┃\n"<<model.registerSnapshot();
    cout << "┣──────────────────────────────────────────────────────────\n"; 
    cout<<"┃\t\t\tMemory\n┃\n" /*model.memorySnippet(0,16)*/;
    uint32_t startAddr = (model.PC >= 8) ? (model.PC - 8) : 0;
    startAddr = (startAddr / 4) * 4; 
    cout << model.memoryWithCurrentPC(startAddr, 6);
    cout << "┣──────────────────────────────────────────────────────────\n"; 
    cout<<"┃\t\tCycles:"<<model.cycles<<" MemR:"<< model.memReads<<"   MemW:"<<model.memWrites<<"\n";
    cout << "┣──────────────────────────────────────────────────────────\n"; 
    cout<<"┃\t\t\tALU ops\n";
    cout << "┃\n"; 
    for(auto&p:model.getALU().getStats()) cout<<"┃  "<<p.first<<":\t\t"<<p.second<<"\n";
    cout << "┣──────────────────────────────────────────────────────────\n"; 
    cout<<"┃\t\t\tInstr counts\n";
    cout << "┃\n"; 
    for(auto&p:model.instrCounts) cout<<"┃  "<<p.first<<":   "<< "\t" <<p.second<<"\n";
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n\n"; 
}

