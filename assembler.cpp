#include "assembler.hpp"
#include <sstream>
#include <iomanip> 

std::vector<std::string> Assembler::assemble(const std::vector<std::string>& assembly) {
    std::vector<std::string> machineCode;
    for (const auto& line : assembly) {
        std::istringstream lineStream(line);
        std::string command, address;
        int opcode = 0, operand = 0;
        lineStream >> command >> address;

        // Convert address or immediate value to integer.........
        if (address[0] == '#') {
            operand = std::stoi(address.substr(1)); // Immediate value......
        }
        else {
            operand = std::stoi(address); // Mem address........
        }

        // Determine the opcode based on the command........
        if (command == "READ") opcode = 10;
        else if (command == "WRITE") opcode = 20;
        else if (command == "LOAD") opcode = 30;
        else if (command == "ADD" && address[0] == '#') {
            opcode = 31; // Special opcode for immediate addition..........
        }
        else if (command == "ADD") {
            opcode = 30; // Normal ADD command............
        }
        else if (command == "STORE") opcode = 21;
        else if (command == "HALT") opcode = 40;

        // format the opcode and operand into a four-digit machine code............
        std::stringstream codeStream;
        codeStream << std::setw(2) << std::setfill('0') << opcode
            << std::setw(2) << std::setfill('0') << operand;

        machineCode.push_back(codeStream.str());
    }
    return machineCode;
}
