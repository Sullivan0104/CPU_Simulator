#include "cpuModel.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

CPUModel::CPUModel(){
    for(auto s: {"add","sub","and","or","slt","lw","sw","beq","j","addi","unknown"})
        instrCounts[s]=0;
}

bool CPUModel::loadMemoryImage(const string& filename){
    bool ok=mem.loadFromFile(filename);
    if(!ok) return false;
    programBound=mem.size();
    mem.ensureSize(max<uint32_t>(programBound,1024));
    return true;
}

static inline uint32_t OPC(uint32_t w){return (w>>26)&0x3F;}
static inline uint32_t RS(uint32_t w){return (w>>21)&0x1F;}
static inline uint32_t RT(uint32_t w){return (w>>16)&0x1F;}
static inline uint32_t RD(uint32_t w){return (w>>11)&0x1F;}
static inline uint32_t FUNCT(uint32_t w){return w&0x3F;}
static inline int32_t  IMM(uint32_t w){return (int16_t)(w&0xFFFF);}
static inline uint32_t ADDR(uint32_t w){return w&0x03FFFFFF;}

bool CPUModel::step(){
    if(halt) return false;
    uint32_t w;
    if(!mem.readWord(PC,w)){ cerr<<"PC out of range\n"; halt=true; return false;}
    cycles++; notify();

    uint32_t opc=OPC(w);
    bool pcSet=false; string name="unknown";

    if(opc==0x00){ // R-type
        uint32_t rs=RS(w),rt=RT(w),rd=RD(w),f=FUNCT(w);
        int32_t rsval=regs.read(rs),rtval=regs.read(rt);
        int32_t res=0;
        switch(f){
            case 0x20: name="add"; res=alu.add(rsval,rtval); regs.write(rd,res); break;
            case 0x22: name="sub"; res=alu.sub(rsval,rtval); regs.write(rd,res); break;
            case 0x24: name="and"; res=alu.band(rsval,rtval); regs.write(rd,res); break;
            case 0x25: name="or";  res=alu.bor(rsval,rtval); regs.write(rd,res); break;
            case 0x2A: name="slt"; res=alu.slt(rsval,rtval); regs.write(rd,res); break;
            default: cerr<<"Bad funct "<<hex<<f<<dec<<"\n"; halt=true; return false;
        }
    }else if(opc==0x23||opc==0x2B||opc==0x04||opc==0x08)
    {
        uint32_t rs=RS(w),rt=RT(w); int32_t imm=IMM(w);
        if(opc==0x23)
        { 
            name="lw"; uint32_t addr=(int32_t)regs.read(rs)+imm;
            memReads++; uint32_t val; if(!mem.readWord(addr,val)){cerr<<"Bad mem\n";halt=true;return false;}
            regs.write(rt,(int32_t)val);
        }else if(opc==0x2B)
        { 
            name="sw"; uint32_t addr=(int32_t)regs.read(rs)+imm;
            memWrites++; if(!mem.writeWord(addr,regs.read(rt))){cerr<<"Bad mem\n";halt=true;return false;}
        }else if(opc==0x04)
        { 
            name="beq";
            int32_t diff=alu.sub(regs.read(rs),regs.read(rt));
            if(diff==0){ PC=(int32_t)PC+4+(imm<<2); pcSet=true;}
        }else if(opc==0x08)
        { 
            name="addi";
            regs.write(rt,alu.add(regs.read(rs),imm));
        }
    }else if(opc==0x02)
    { 
        name="j";
        uint32_t target=(PC & 0xF0000000u)|(ADDR(w)<<2);
        PC=target; pcSet=true;
    }else
    {
        cerr<<"Illegal opcode "<<hex<<opc<<dec<<"\n"; halt=true; return false;
    }

    instrCounts[name]++;
    if(!pcSet) PC+=4;
    notify();
    return true;
}

string CPUModel::registerSnapshot() const{
    ostringstream oss;
    for(int i=0;i<32;i++)
    {
        oss<<"$"<<setw(2)<<i<<": "<<setw(11)<<regs.read(i);
        if(i%4==3) oss<<"\n"; else oss<<"  ";
    }
    return oss.str();
}
string CPUModel::memorySnippet(uint32_t start,uint32_t words) const{
    ostringstream oss;
    for(uint32_t i=0;i<words;i++)
    {
        uint32_t a=start+i*4;
        if(a+4<=mem.size())
        {
            uint32_t w; mem.readWord(a,w);
            oss<<hex<<setw(8)<<setfill('0')<<a<<": "<<setw(8)<<w<<dec<<"\n";
        }
    }
    return oss.str();
}
