#include "Visitor.hpp"
#include "Expression.hpp"
#include "NumericExpression.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"

using namespace llvm;

static LLVMContext* TheContext;
static Module* TheModule;
static IRBuilder<>* Builder;
static std::map<std::string, Value*> NamedValues;

IRVisitor::IRVisitor() {}
IRVisitor::~IRVisitor() {}

Symbol IRVisitor::visit(Context ctx, NumericConstant& num) {
    double value = num.getValue();
    Value* constantFp = ConstantFP::get(*TheContext, APFloat(value));
}
