// the symbol as the return for each node
#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include "Meta.hpp"

#include "llvm/IR/Value.h"
#include <string>

using namespace llvm;

class Symbol {
private:
    std::string name; // Symbol Name
    TypeInfo type;
    std::string stringValue;
    double dblValue;
    bool boolenValue;
    Value* llvmValue;

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

    llvm::Value* getLlvmValue();
    void setLlvmValue(llvm::Value* val);
};

#endif // SYMBOL_HPP
