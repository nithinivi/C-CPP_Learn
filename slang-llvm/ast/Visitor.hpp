
// forward declaration
class NumericConstant;
class BinaryExpr;
class UnaryExpr;
class IExprVisitor;

#ifndef VISITOR_H
#define VISITOR_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"

#include "Context.hpp"
#include "Symbol.hpp"
#include <map>
#include <string>

// static LLVMContext* TheContext;
class IExprVisitor {

public:
    virtual Symbol& visit(Context ctx, NumericConstant& num) = 0;
    virtual Symbol& visit(Context ctx, BinaryExpr& bin) = 0;
    virtual Symbol& visit(Context ctx, UnaryExpr& un) = 0;
};

class IRVisitor : public IExprVisitor {
    Module* TheModule;
    IRBuilder<>* Builder;
    LLVMContext* TheContext;

public:
    IRVisitor();
    ~IRVisitor();

    Module* getLlvmModule();

    Symbol& visit(Context ctx, NumericConstant& num);
    Symbol& visit(Context ctx, BinaryExpr& bin);
    Symbol& visit(Context ctx, UnaryExpr& un);
};

#endif // !1
