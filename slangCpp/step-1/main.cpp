#include "ast.h"


using namespace ast;


int main()
{

     RuntimeContext* ctx;
     NumericConstant e(1.1);
     printf("%f \n", e.evaluate(ctx));
     BinaryExp ee(new NumericConstant(0.1) ,  new NumericConstant(0.1) , OP_PLUS);
     printf("%f \n", ee.evaluate(ctx));

     // printf("%f \n" , e->evaluate(ctx));

     // return 0;
}
