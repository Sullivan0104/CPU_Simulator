#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>
#include "subject.hpp"
#include "registers.hpp"
#include "memory.hpp"
#include "alu.hpp"

class CPUModel : public Subject {
public:
    CPUModel();
    bool loadMemoryImage(const std::string& filename);
    bool step();           // execute one instruction
    bool halted() const { return halt; }

    // info for views
    std::string registerSnapshot() const;
    std::string memorySnippet(uint32_t start=0,uint32_t words=8) const;

    // stats (public for simplicity)
    uint32_t PC=0;
    uint64_t cycles=0;
    uint32_t memReads=0, memWrites=0;
    std::unordered_map<std::string,uint32_t> instrCounts;

    const ALU& getALU() const { return alu; }
private:
    Registers regs;
    Memory mem;
    ALU alu;
    bool halt=false;
    uint32_t programBound=0;
};
