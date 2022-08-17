#include "Symbol.hpp"

Symbol::Symbol() {}
Symbol::~Symbol() {}

Symbol::Symbol(TypeInfo type_) { this->type = type_; }

Symbol::Symbol(std::string name, TypeInfo type) {
    this->name = name;
    this->type = type;
}

std::string Symbol::getName() { return name; };
void Symbol::setName(std::string name) { this->name = name; };

TypeInfo Symbol::getType() { return type; };
void Symbol::setType(TypeInfo type) { this->type = type; };

std::string Symbol::getStringValue() { return stringValue; }
void Symbol::setStringValue(std::string str) { this->stringValue = str; }

double Symbol::getdblValue() { return dblValue; }
void Symbol::setdblValue(double dbl) { this->dblValue = dbl; }

bool Symbol::getboolValue() { return boolenValue; }
void Symbol::setBoolValue(bool bl) { this->boolenValue = bl; }
