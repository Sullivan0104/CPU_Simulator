#include "alu.hpp"

ALU::ALU() {
    stats = {{"add",0},{"sub",0},{"and",0},{"or",0},{"slt",0}};
}

int ALU::add(int a,int b){ 
    stats["add"]++; 
    return a+b; 
}

int ALU::sub(int a,int b){ 
    stats["sub"]++; 
    return a-b; 
}

int ALU::_and(int a,int b){ 
    stats["and"]++; 
    return a&b; 
}

int ALU::_or(int a,int b){ 
    stats["or"]++; 
    return a|b; 
}

int ALU::slt(int a,int b){ 
    stats["slt"]++; 
    return (a<b)?1:0; 
}

const std::unordered_map<std::string, int>& ALU::getStats() const{
    return stats;
}
