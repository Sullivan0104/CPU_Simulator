#pragma once
#include <vector>
#include <cstdint>
#include <string>

class Memory {
public:
    bool loadFromFile(const std::string& filename);
    bool readWord(uint32_t addr, uint32_t &out) const;
    bool writeWord(uint32_t addr, uint32_t value);
    void ensureSize(uint32_t bytes);
    uint32_t size() const;
    
private:
    std::vector<uint8_t> mem;
};
