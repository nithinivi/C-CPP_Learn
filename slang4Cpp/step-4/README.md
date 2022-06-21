# Slang 4 Cpp

- build with cmake 
- support assignment
- data types
- variables

## Usage

```bash
mkdir build
cd build
cmake -s ../ -B . && make -k && ./slang

```

## File Structure

├── builder
│   └── builder.cpp
├── context
│   └── SymbolTable.cpp
├── expressions
│   ├── BinaryDiv.cpp
│   ├── BinaryMinus.cpp
│   ├── BinaryMul.cpp
│   ├── BinaryPlus.cpp
│   ├── BoolenConstant.cpp
│   ├── Expression.cpp
│   ├── NumericConstant.cpp
│   ├── StringLiteral.cpp
│   ├── UnaryMinus.cpp
│   ├── UnaryPlus.cpp
│   └── Variable.cpp
├── frontend
│   ├── expressionParser.cpp
│   ├── lexer.cpp
│   └── statementParser.cpp
├── include
│   ├── ast_expression.h
│   ├── ast.h
│   ├── ast_statement.h
│   ├── builder.h
│   ├── common.h
│   ├── context.h
│   ├── lexer.h
│   ├── parser.h
│   └── SlangConfig.h
├── main.cpp
├── statements
│   ├── AssignmentStatement.cpp
│   ├── statement.cpp
│   └── VariableDeclStatement.cpp
└── tree.txt



## Reference 

[1] https://github.com/praseedpai/SlangForDotNet

[2] https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html
