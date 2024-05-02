#include <string>
#include <unordered_map>

class SymbolTable {
private:
    std::unordered_map<std::string, int> symbols;
    int nextAddress;

public:
    SymbolTable();
    int get_address(const std::string& symbol);
    bool add_symbol(const std::string& symbol);
};

