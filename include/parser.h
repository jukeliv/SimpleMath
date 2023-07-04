#ifndef PARSER_H_
#define PARSER_H_

#include "lexer.h"

/*
    conditional -> "when" STRING program "end";
    program -> list[expresion];
    expresion -> group | set | function;
    function -> ID group;
    group -> "(" list[literal] ")";
    Set -> ID "=" literal;
    literal -> STRING | ID;
*/

typedef enum
{
    Literal,
    BinOp,
    Parenthesized
}Expr_Type;

struct Expr;
typedef struct
{
    size_t heap;
    size_t size;
    struct Expr* content;
}Expr_List;


typedef struct Expr
{
    Expr_Type type;
    union
    {
        struct{
            int value;
        }Literal;
        struct{
            struct Expr* left;
            BinaryOperators op;
            struct Expr* right;
        }BinOp;
        struct{
            struct Expr* expr;
        }Parenthesized;
    }e;
}Expr;

Expr Expr_Literal(Token tok);
Expr Expr_BinOp(BinaryOperators op, Expr left, Expr right);
Expr Expr_Parenthesized(Expr node);

Expr Parse_BinOp(size_t* i, Token_List* tokens);
Expr Parse_Tokens(size_t* i, Token_List* tokens);
Expr Parse_Program(Token_List* tokens);

#endif // PARSER_H_