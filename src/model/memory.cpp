#include "memory.hpp"
#include <fstream>

bool Memory::loadFromFile(const std::string& filename){
    std::ifstream fin(filename, std::ios::binary);
    if(!fin) return false;
    fin.seekg(0,std::ios::end);
    auto sz=fin.tellg();
    fin.seekg(0,std::ios::beg);
    mem.resize(sz);
    fin.read(reinterpret_cast<char*>(mem.data()),sz);
    return true;
}

bool Memory::readWord(uint32_t addr,uint32_t &out) const{
    if(addr+4>mem.size()) return false;
    out = (mem[addr]<<24)|(mem[addr+1]<<16)|(mem[addr+2]<<8)|mem[addr+3];
    return true;
}

bool Memory::writeWord(uint32_t addr,uint32_t value){
    if(addr+4>mem.size()) return false;
    mem[addr]=(value>>24)&0xFF;
    mem[addr+1]=(value>>16)&0xFF;
    mem[addr+2]=(value>>8)&0xFF;
    mem[addr+3]=value&0xFF;
    return true;
}

void Memory::ensureSize(uint32_t bytes){ 
    if(mem.size()<bytes) mem.resize(bytes,0); 
}

uint32_t Memory::size() const { return static_cast<uint32_t>(mem.size()); }
