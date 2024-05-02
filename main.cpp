#include "compiler.hpp"
#include "assembler.hpp"
#include "mysimpletron.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//x = 1000 in the input.txt file.......
//if you change the constant make sure its not in three digits only two digits......



int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream assemblyFile("assembly.txt", std::ios::out | std::ios::trunc);
    std::ofstream machineCodeFile("machine_code.txt", std::ios::out | std::ios::trunc);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file.\n";
        return 1;
    }

    // Read entire input file into a string
    std::string code((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    Compiler compiler;
    Assembler assembler;

    // Compile the code into initial assembly
    auto assembly = compiler.compile(code);

    // Write the updated assembly code to a file
    for (const auto& line : assembly) {
        assemblyFile << line << std::endl;
    }
    assemblyFile.close();

    // Assemble the updated assembly into machine code
    auto machineCode = assembler.assemble(assembly);

    // Write machine code to a file
    for (const auto& line : machineCode) {
        machineCodeFile << line << std::endl;
    }
    machineCodeFile.close();

    // Open machine code file for execution
    std::ifstream machineCodeInput("machine_code.txt");
    if (!machineCodeInput.is_open()) {
        std::cerr << "Error opening machine code file.\n";
        return 1;
    }

    // Read the machine code from the file
    Simpletron simpletron(100);
    std::vector<int> program;
    std::string machineLine;
    while (getline(machineCodeInput, machineLine)) {
        if (!machineLine.empty()) {
            program.push_back(std::stoi(machineLine));
        }
    }
    machineCodeInput.close();

    // Load and execute the updated machine code in the Simpletron
    simpletron.load_program(program);
    simpletron.execute();

    // Optionally, dump the final state of the Simpletron
    simpletron.dump();

    return 0;
}
