#include "Visitor.hpp"
#include "llvm/IR/Constants.h"

using namespace llvm;

IRVisitor::IRVisitor() {}
IRVisitor::~IRVisitor() {}

Symbol IRVisitor::visit(Context ctx, NumericConstant& num) {
    value = num.getValue();
    Value constantFp = ConstantFP::get(*TheContext, APFloat(value));
    
}
