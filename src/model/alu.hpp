#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>

class ALU {
public:
    ALU();
    int32_t add(int32_t a, int32_t b);
    int32_t sub(int32_t a, int32_t b);
    int32_t band(int32_t a, int32_t b);
    int32_t bor(int32_t a, int32_t b);
    int32_t slt(int32_t a, int32_t b);
    const std::unordered_map<std::string, uint32_t>& stats() const;
private:
    std::unordered_map<std::string, uint32_t> opCounts;
};
