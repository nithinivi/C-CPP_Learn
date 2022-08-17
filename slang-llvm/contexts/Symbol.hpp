// the symbol as the return for each node
#ifndef SYMBOL_HPP
#define SYMBOL_HPP
#include "Meta.hpp"
#include <string>

class Symbol {
private:
    std::string name; // Symbol Name
    TypeInfo type;
    std::string stringValue;
    double dblValue;
    bool boolenValue;

public:
    Symbol();
    Symbol(TypeInfo type);
    Symbol(std::string name, TypeInfo type);
    ~Symbol();

    std::string getName();
    void setName(std::string name);

    TypeInfo getType();
    void setType(TypeInfo type);

    std::string getStringValue();
    void setStringValue(std::string str);

    double getdblValue();
    void setdblValue(double dbl);

    bool getboolValue();
    void setBoolValue(bool bl);
};

#endif // SYMBOL_HPP
