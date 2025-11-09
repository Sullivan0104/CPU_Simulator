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
    
    // Load binary memory image
    bool loadMemoryImage(const std::string& filename);
    
    // Execute one instruction, return false if error/halt
    bool step();
    
    // Check if CPU is halted
    bool halted() const { return halt; }
    
    // State inspection methods
    std::string registerSnapshot() const;
    std::string memorySnippet(uint32_t start, uint32_t words) const;
    const ALU& getALU() const { return alu; }
    
    // Public statistics
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
    
    // Fetch instruction from memory
    uint32_t fetch();
    
    // Execute different instruction types
    void executeRType(uint32_t instr);
    void executeIType(uint32_t instr, uint8_t opcode);
    void executeJType(uint32_t instr);
};
