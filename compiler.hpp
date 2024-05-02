

#include <string>
#include <vector>
#include "symbolTable.hpp"

class Compiler {
private:
    SymbolTable symbolTable;

public:
    std::vector<std::string> compile(const std::string& code);
};


