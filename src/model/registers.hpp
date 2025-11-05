#pragma once
#include <array>
#include <cstdint>

class Registers 
{
public:
    Registers();
    void write(unsigned idx, int32_t val);
    int32_t read(unsigned idx) const;
private:
    std::array<int32_t, 32> regs;
};
