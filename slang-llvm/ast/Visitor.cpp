#include "Visitor.hpp"
#include "Expression.hpp"
#include "NumericExpression.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include <stdexcept>

using namespace llvm;

IRVisitor::IRVisitor() {
    this->TheContext = new LLVMContext();
    this->TheModule = new Module("SLANG JIT", *TheContext);

    // Create a new builder for the module.
    this->Builder = new IRBuilder<>(*TheContext);
}
IRVisitor::~IRVisitor() {}

Module* IRVisitor::getLlvmModule() { return TheModule; }

Symbol& IRVisitor::visit(Context ctx, NumericConstant& num) {
    Value* constantFp = ConstantFP::get(*TheContext, APFloat(num.getValue()));
    Symbol& symbol = num.getSymbol();
    symbol.setLlvmValue(constantFp);
    return symbol;
}

Symbol& IRVisitor::visit(Context ctx, BinaryExpr& binaryExpr) {
    Symbol& left = binaryExpr.getLeft().accept(ctx, *this);
    Symbol& right = binaryExpr.getRight().accept(ctx, *this);

    if (left.getType() != right.getType() && left.getType() != TYPE_NUMERIC)
        throw std::runtime_error("type error in binaryExpr ");

    switch (binaryExpr.getOp()) {
    case OPERATOR::PLUS:
        Builder->CreateFAdd(left.getLlvmValue(), right.getLlvmValue(),
                            "add_bi");
        break;
    case OPERATOR::MINUS:
        Builder->CreateFSub(left.getLlvmValue(), right.getLlvmValue(),
                            "sub_bi");
        break;
    case OPERATOR::MUL:
        Builder->CreateFMul(left.getLlvmValue(), right.getLlvmValue(),
                            "mul_bi");
        break;
    case OPERATOR::DIV:
        Builder->CreateFDiv(left.getLlvmValue(), right.getLlvmValue(),
                            "div_bi");
        break;

    default:
        throw std::runtime_error("invalid binary operator ");
    }

    return left;
}

Symbol& IRVisitor::visit(Context ctx, UnaryExpr& unaryExpr) {
    Symbol& exp = unaryExpr.getExp().accept(ctx, *this);

    if (exp.getType() != TYPE_NUMERIC)
        throw std::runtime_error("type error in unaryExpr ");

    Value* zeroFp = ConstantFP::get(*TheContext, APFloat(0.0));

    switch (unaryExpr.getOp()) {
    case OPERATOR::PLUS:
        Builder->CreateFAdd(zeroFp, exp.getLlvmValue(), "add_un");
        break;
    case OPERATOR::MINUS:
        Builder->CreateFSub(zeroFp, exp.getLlvmValue(), "sub_un");
        break;
    default:
        throw std::runtime_error("invalid uinary operator ");
    }
    return exp;
}