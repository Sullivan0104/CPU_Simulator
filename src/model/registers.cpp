#include "registers.hpp"

Registers::Registers() { regs.fill(0); }

void Registers::write(unsigned idx,int32_t val){ if(idx!=0) regs[idx]=val; }

int32_t Registers::read(unsigned idx) const{ return regs[idx]; }
