#include "..\include\lexer.h"

void Token_List_Init(Token_List* tokens)
{
    tokens->size = 0;
    tokens->heap = 1;
    tokens->content = malloc(tokens->heap * sizeof(Token));
    if (!tokens->content)
    {
        printf("ERROR: Couldn't allocate memory for Token_List\n");
        exit(1);
    }
}

void Token_List_Push(Token_List* tokens, Token tok)
{
    if (tokens->size >= tokens->heap)
    {
        tokens->heap *= 2;
        tokens->content = realloc(tokens->content, tokens->heap * sizeof(Token));
        if (!tokens->content)
        {
            printf("ERROR: Couldn't allocate memory for Token_List\n");
            exit(1);
        }
    }
    tokens->content[tokens->size++] = tok;
}

void Token_List_Free(Token_List* tokens)
{
    tokens->heap = 0;
    tokens->size = 0;
    if(tokens->content)
        free(tokens->content);
}

Token Token_New(Token_Type type)
{
    Token tok;
	tok.type = type;
    tok.num = 0;
	return tok;
}

Token Token_New_Num(Token_Type type, float num)
{
    Token tok;
	tok.type = type;
    tok.num = num;
	return tok;
}

bool is_num(char c)
{
    return (c >= '1' && c <= '9');
}

bool is_white_space(char c)
{
    return (c == '\n' || c == ' ') || (c == '\r' || c == '\t');
}

int Tokenize_File(Token_List* tokens, const char* source)
{
    size_t lex_i = 0;
    char lex[0xffff] = {0};

    for (size_t i = 0; i < strlen(source); ++i)
    {
        while(is_white_space(source[i]))
        {
            ++i;
        }

        lex_i = 0;
        memset(lex, 0, 0xffff);

        switch (source[i])
        {
            case '+':
                Token_List_Push(tokens, Token_New_Num(TOK_BINOP, BINOP_PLUS));
            continue;
            
            case '-':
                Token_List_Push(tokens, Token_New_Num(TOK_BINOP, BINOP_MINUS));
            continue;
            
            case '*':
                Token_List_Push(tokens, Token_New_Num(TOK_BINOP, BINOP_MULTIPLICATION));
            continue;
            
            case '/':
                Token_List_Push(tokens, Token_New_Num(TOK_BINOP, BINOP_DIVISION));
            continue;

            case '(':
                Token_List_Push(tokens, Token_New(TOK_OPEN_PARENTHESIS));
            continue;

            case ')':
                Token_List_Push(tokens, Token_New(TOK_CLOSE_PARENTHESIS));
            continue;

            default:
                if(is_num(source[i]))
                {
                    while(is_num(source[i]) || source[i] == '.')
                    {
                        lex[lex_i++] = source[i++];
                    }
                    Token_List_Push(tokens, Token_New_Num(TOK_NUM, strtod(lex, NULL)));
                    i-=1; // if you made this "1+1+1a", the compiler would tell you :)
                    continue;
                }
                else if (!is_white_space(source[i]) && source[i] != '\0')
                {
                    printf("ERROR: Unknown character found in file!!! ( %c : %d )\n", source[i], source[i]);
                    return 1;
                }
            break;
        }
    }

    return 0;
}