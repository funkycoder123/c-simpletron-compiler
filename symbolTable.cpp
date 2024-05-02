#include "symbolTable.hpp"

SymbolTable::SymbolTable() : nextAddress(0) {}

int SymbolTable::get_address(const std::string& symbol) {
    auto it = symbols.find(symbol);
    if (it != symbols.end()) {
        return it->second;
    }
    return -1; // symbol not found
}

bool SymbolTable::add_symbol(const std::string& symbol) {
    if (symbols.find(symbol) == symbols.end()) {
        symbols[symbol] = nextAddress++;
        return true;
    }
    return false;
}
