#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

float Interpret(Expr node);

float Interpret_Literal(Expr node);
float Interpret_BinOp(Expr node);
float Interpret(Expr node);

#endif // INTERPRETER_H_
