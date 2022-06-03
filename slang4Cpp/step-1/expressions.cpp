#include "ast.h"

using namespace ast;

Exp::Exp(){};
Exp::~Exp(){};



NumericConstant::NumericConstant(double value){
     this->value = value;
}

double NumericConstant::evaluate(RuntimeContext *ctx){
     return value;
}

NumericConstant::~NumericConstant(){};




BinaryExp::BinaryExp(Exp *left, Exp *right, Operator op){
     this->left = left;
     this->right = right;
     this->op = op;
}

double BinaryExp::evaluate(RuntimeContext *ctx){
     switch(op)
     {

     case OP_PLUS:
          return left->evaluate(ctx) + right->evaluate(ctx);
     case OP_MINUS:
          return left->evaluate(ctx) - right->evaluate(ctx);
     case OP_MUL:
          return left->evaluate(ctx) * right->evaluate(ctx);
     case OP_DIV:
          return left->evaluate(ctx) / right->evaluate(ctx);

     default:
          throw std::runtime_error("Unsupported Operator");
     }
}

BinaryExp::~BinaryExp(){
     delete left;
     delete right;
}




UnaryExp::UnaryExp(Exp *expression, Operator op) {
     this->expression = expression;
     this->op =op;
}


double UnaryExp::evaluate(RuntimeContext *ctx){
     switch(op){
     case OP_PLUS:
          return expression->evaluate(ctx);
     case OP_MINUS:
          return -expression->evaluate(ctx);

     default:
          throw std::runtime_error("Unsupported Operator");
     }
}


UnaryExp::~UnaryExp(){
     delete expression;
}
