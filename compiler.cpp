#include "compiler.hpp"
#include <sstream>
#include <regex>

std::vector<std::string> Compiler::compile(const std::string& code) {
    std::vector<std::string> assembly;
    std::istringstream iss(code);
    std::string line;
    while (getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string command;
        lineStream >> command;

        if (command == "input") {
            std::string var;
            lineStream >> var;
            symbolTable.add_symbol(var);
            assembly.push_back("READ " + std::to_string(symbolTable.get_address(var)));
        }
        else if (command == "print") {
            std::string var;
            lineStream >> var;
            assembly.push_back("WRITE " + std::to_string(symbolTable.get_address(var)));
        }
        else if (command == "let") {
            std::string var, equals, operand1, op, operand2;
            lineStream >> var >> equals >> operand1 >> op >> operand2;
            if (op == "+") {
                assembly.push_back("LOAD " + std::to_string(symbolTable.get_address(operand1)));
                if (std::regex_match(operand2, std::regex("[0-9]+"))) { // Check if operand2 is a number...
                    // Since the memory is limited, handling for constants directly isn't supported, simulate with temporary......
                    assembly.push_back("ADD #" + operand2); // will assume ADD #num is a valid for adding immediate values
                }
                else {
                    assembly.push_back("ADD " + std::to_string(symbolTable.get_address(operand2)));
                }
                assembly.push_back("STORE " + std::to_string(symbolTable.get_address(var)));
            }
        }
        else if (command == "end") {
            assembly.push_back("HALT 0");
        }
    }
    return assembly;
}
