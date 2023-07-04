#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    BINOP_PLUS,
    BINOP_MINUS,
    BINOP_DIVISION,
    BINOP_MULTIPLICATION
}BinaryOperators;

typedef enum Token_Type {
    TOK_NUM,
    TOK_BINOP,
    TOK_OPEN_PARENTHESIS,
    TOK_CLOSE_PARENTHESIS
} Token_Type;

typedef struct Token {
    Token_Type type;
    float num;
} Token;

typedef struct Token_List {
    size_t heap;
    size_t size;
    Token* content;
} Token_List;

Token Token_New(Token_Type type);
Token Token_New_Num(Token_Type type, float num);

void Token_List_Init(Token_List* tokens);
void Token_List_Push(Token_List* tokens, Token tok);
void Token_List_Free(Token_List* tokens);

bool is_num(char c);
bool is_white_space(char c);

int Tokenize_File(Token_List* tokens, const char* source);

#endif // LEXER_H_
