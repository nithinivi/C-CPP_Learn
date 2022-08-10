#pragma once

#ifndef COMMON_H

#include <map>
#include <string>

#include "llvm/IR/LLVMContext.h"

#define COMMON_H

static llvm::LLVMContext *TheContext = new llvm::LLVMContext();

enum Operator { OP_PLUS, OP_MINUS, OP_MUL, OP_DIV };
enum TYPE_INFO { TYPE_ILLEGAL, TYPE_NUMERIC, TYPE_BOOL, TYPE_STRING };

#endif /* COMMON_H */
