// the symbol as the return for each node
#include <string>

#if !defined(SYMBOL_HPP)
#define SYMBOL_HPP

#include "meta.hpp"

class Symbol {
private:
    std::string name; // Symbol Name
    Type type;
    std::string stringValue;
    double dblValue;
    bool boolenValue;

public:
    Symbol();
    Symbol(Type type);
    Symbol(std::string name, Type type);
    ~Symbol();

    std::string getName();
    void setName(std::string name);

    Type getType();
    void setType(Type type);

    std::string getStringValue();
    void setStringValue(std::string str);

    double getdblValue();
    void setdblValue(double dbl);

    bool getboolValue();
    void setBoolValue(bool bl);
};

#endif // SYMBOL_HPP
