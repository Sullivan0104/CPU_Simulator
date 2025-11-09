#pragma once
#include <unordered_map>
#include <string>

class ALU {
public:
    ALU();

    int add(int a, int b);
    int sub(int a, int b);
    int _and(int a, int b);
    int _or(int a, int b);
    int slt(int a, int b);

    const std::unordered_map<std::string, int>& getStats() const;

private:
    std::unordered_map<std::string, int> stats;
};
