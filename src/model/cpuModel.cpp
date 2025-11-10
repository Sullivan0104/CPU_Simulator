#include "cpuModel.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

CPUModel::CPUModel() : PC(0), cycles(0), memReads(0), memWrites(0), halt(false) 
{
    // Initialize instruction counters
    instrCounts = {
        {"add", 0}, {"sub", 0}, {"and", 0}, {"or", 0}, {"slt", 0},
        {"lw", 0}, {"sw", 0}, {"beq", 0}, {"addi", 0}, {"j", 0}
    };
}

bool CPUModel::loadMemoryImage(const string& filename)
{
    if(!mem.loadFromFile(filename)) return false;
    
    mem.ensureSize(1024);
    
    return true;
}

uint32_t CPUModel::fetch()
{
    uint32_t instr;
    if(!mem.readWord(PC, instr)) {
        cerr << "Fetch error at PC=0x" << hex << PC << dec << "\n";
        halt = true;
        return 0;
    }
    memReads++;
    return instr;
}

bool CPUModel::step()
{
    if(halt) return false;
    
    uint32_t instr = fetch();
    if(halt) return false;
    
    uint8_t opcode = (instr >> 26) & 0x3F;
    
    
    //notify();
    
    if(opcode == 0x00) {
        executeRType(instr);
    } else if(opcode == 0x02) {
        executeJType(instr);
    } else {
        executeIType(instr, opcode);
    }
    
    cycles++;

    notify();

    return !halt;
}

void CPUModel::executeRType(uint32_t instr)
{
    uint8_t funct = instr & 0x3F;
    int rs = (instr >> 21) & 0x1F;
    int rt = (instr >> 16) & 0x1F;
    int rd = (instr >> 11) & 0x1F;
    
    int32_t rsVal = regs.read(rs);
    int32_t rtVal = regs.read(rt);
    int32_t result = 0;
    
    switch(funct) {
        case 0x20: // add
            result = alu.add(rsVal, rtVal);
            regs.write(rd, result);
            instrCounts["add"]++;
            break;
        case 0x22: // sub
            result = alu.sub(rsVal, rtVal);
            regs.write(rd, result);
            instrCounts["sub"]++;
            break;
        case 0x24: // and
            result = alu._and(rsVal, rtVal);
            regs.write(rd, result);
            instrCounts["and"]++;
            break;
        case 0x25: // or
            result = alu._or(rsVal, rtVal);
            regs.write(rd, result);
            instrCounts["or"]++;
            break;
        case 0x2A: // slt
            result = alu.slt(rsVal, rtVal);
            regs.write(rd, result);
            instrCounts["slt"]++;
            break;
        default:
            cerr << "Unknown R-type funct: 0x" << hex << (int)funct << dec << "\n";
            halt = true;
            return;
    }
    
    PC += 4;
}

void CPUModel::executeIType(uint32_t instr, uint8_t opcode)
{
    int rs = (instr >> 21) & 0x1F;
    int rt = (instr >> 16) & 0x1F;
    int16_t imm = instr & 0xFFFF; // Sign-extended immediate
    
    int32_t rsVal = regs.read(rs);
    
    switch(opcode) {
        case 0x08: // addi
        {
            int32_t result = alu.add(rsVal, imm);
            regs.write(rt, result);
            instrCounts["addi"]++;
            PC += 4;
            break;
        }
        case 0x23: // lw
        {
            uint32_t addr = rsVal + imm;
            uint32_t data;
            if(!mem.readWord(addr, data)) {
                cerr << "Memory read error at 0x" << hex << addr << dec << "\n";
                halt = true;
                return;
            }
            memReads++;
            regs.write(rt, static_cast<int32_t>(data));
            instrCounts["lw"]++;
            PC += 4;
            break;
        }
        case 0x2B: // sw
        {
            uint32_t addr = rsVal + imm;
            int32_t data = regs.read(rt);
            if(!mem.writeWord(addr, static_cast<uint32_t>(data))) {
                cerr << "Memory write error at 0x" << hex << addr << dec << "\n";
                halt = true;
                return;
            }
            memWrites++;
            instrCounts["sw"]++;
            PC += 4;
            break;
        }
        case 0x04: // beq
        {
            int32_t rtVal = regs.read(rt);
            int32_t cmp = alu.sub(rsVal, rtVal); // ALU sub operation for comparison
            instrCounts["beq"]++;
            if(cmp == 0) {
                PC = PC + 4 + (imm << 2); // Branch offset is word-aligned
            } else {
                PC += 4;
            }
            break;
        }
        default:
            cerr << "Unknown I-type opcode: 0x" << hex << (int)opcode << dec << "\n";
            halt = true;
            return;
    }
}

void CPUModel::executeJType(uint32_t instr)
{
    uint32_t addr = instr & 0x03FFFFFF;
    
    // Jump address (word-aligned, keeping upper PC bits)
    PC = (addr  << 2);
    instrCounts["j"]++;
}

std::string CPUModel::registerSnapshot() const
{
    std::ostringstream oss;
    for(int i = 0; i < 32; i++) {     
        oss << "$" << std::setw(2) << i << " = ";

        std::ostringstream value;
        value << std::setw(7) << regs.read(i);

        oss << "\033[31m" << value.str() << "\033[0m";

        if ((i + 1) % 4 == 0) oss << "\n";
        else oss << "  "; 
    }
    return oss.str();
}

string CPUModel::memorySnippet(uint32_t start, uint32_t words) const
{
    ostringstream oss;
    for(uint32_t i = 0; i < words; i++) {
        uint32_t addr = start + (i * 4);
        uint32_t data;
        if(mem.readWord(addr, data)) {
            oss << "0x" << hex << setw(8) << setfill('0') << addr 
                << ": 0x" << setw(8) << setfill('0') << data 
                << dec << "\n";
        }
    }
    return oss.str();
}
