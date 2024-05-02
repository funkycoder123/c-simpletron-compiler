#include "mysimpletron.hpp"

#include <iomanip>

Simpletron::Simpletron(int size) : memory(size, 0) {} //inti memory..

void Simpletron::load_program(const std::vector<int>& program) {
    for (size_t i = 0; i < program.size() && i < memory.size(); ++i) {
        memory[i] = program[i];
    }
}
void Simpletron::execute() {
    bool running = true;
    while (running && instructionCounter < memory.size()) {
        instructionRegister = memory[instructionCounter];
        operationCode = instructionRegister / 100;  // Parse the opcode
        operand = instructionRegister % 100;        // Parse the operand

        switch (operationCode) {
        case 10:  // Read and store at operand
            // Skipped reading from user, assume data is preset
            break;
        case 20:  // Write from operand
            std::cout << "> " << memory[operand] << std::endl;
            break;
        case 30:  // Load from operand
            accumulator = memory[operand];
            break;
        case 31:  // Add immediate value
            accumulator += operand;
            break;
        case 21:  // Store into operand
            memory[operand] = accumulator;
            break;
        case 40:  // Halt
            running = false;
            break;
        default:
            std::cerr << "Error: Invalid operation code " << operationCode << std::endl;
            running = false;
            break;
        }
        instructionCounter++;
    }
}

void Simpletron::dump() const {
    std::cout << "\nRegisters:\n";
    std::cout << "accumulator:           " << std::setw(5) << accumulator << std::endl;
    std::cout << "instructionCounter:    " << std::setw(5) << instructionCounter << std::endl;
    std::cout << "instructionRegister:   " << std::setw(5) << instructionRegister << std::endl;
    std::cout << "operationCode:         " << std::setw(5) << operationCode << std::endl;
    std::cout << "operand:               " << std::setw(5) << operand << std::endl;
    std::cout << "\nMemory:\n";
    for (int i = 0; i < memory.size(); ++i) {
        if (i % 10 == 0) {
            std::cout << std::endl;
        }
        std::cout << std::setw(5) << memory[i];
    }
    std::cout << std::endl;
}
