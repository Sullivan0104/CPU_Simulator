#include "alu.hpp"

ALU::ALU() {
    opCounts = {{"add",0},{"sub",0},{"and",0},{"or",0},{"slt",0}};
}
int32_t ALU::add(int32_t a,int32_t b){ opCounts["add"]++; return a+b; }
int32_t ALU::sub(int32_t a,int32_t b){ opCounts["sub"]++; return a-b; }
int32_t ALU::band(int32_t a,int32_t b){ opCounts["and"]++; return a&b; }
int32_t ALU::bor(int32_t a,int32_t b){ opCounts["or"]++; return a|b; }
int32_t ALU::slt(int32_t a,int32_t b){ opCounts["slt"]++; return (a<b)?1:0; }
const std::unordered_map<std::string,uint32_t>& ALU::stats() const { return opCounts; }
