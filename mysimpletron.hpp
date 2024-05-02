#include <vector>
#include <iostream>

class Simpletron {
private:
    std::vector<int> memory;
    int accumulator = 0;
    int instructionCounter = 0;
    int instructionRegister = 0;
    int operationCode = 0;
    int operand = 0;

public:
    Simpletron(int size);
    void load_program(const std::vector<int>& program);
    void execute();
    void dump() const;
};


