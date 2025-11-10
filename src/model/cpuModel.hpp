#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>
#include "subject.hpp"
#include "registers.hpp"
#include "memory.hpp"
#include "alu.hpp"

class CPUModel : public Subject
{
public:
    CPUModel();
    
    bool loadMemoryImage(const std::string& filename);
    
    bool step();
    
    bool halted() const { return halt; }
    
    std::string registerSnapshot() const;
    std::string memorySnippet(uint32_t start, uint32_t words) const;
    const ALU& getALU() const { return alu; }
    
    uint32_t PC;
    int cycles;
    int memReads;
    int memWrites;
    std::unordered_map<std::string, int> instrCounts;
    
private:
    Registers regs;
    Memory mem;
    ALU alu;
    bool halt;
    
    uint32_t fetch();
    
    void executeRType(uint32_t instr);
    void executeIType(uint32_t instr, uint8_t opcode);
    void executeJType(uint32_t instr);
};
