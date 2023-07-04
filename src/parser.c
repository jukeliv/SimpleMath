#include "..\include\parser.h"

Expr Expr_Literal(Token tok)
{
    Expr literal;
    literal.type = Literal;
    literal.e.Literal.value = tok.num;
    if(tok.type != TOK_NUM)
    {
        printf("ERROR: Can't set Literal to Token Type!!! ( %d )\n", tok.type);
        exit(1);
    }
    return literal;
}

Expr Expr_BinOp(BinaryOperators op, Expr left, Expr right)
{
    Expr expr;
    
    expr.type = BinOp;

    // Assign the left operand directly
    expr.e.BinOp.left = malloc(sizeof(Expr));
    *expr.e.BinOp.left = left;


    expr.e.BinOp.op = op;
    
    // Assign the right operand directly
    expr.e.BinOp.right = malloc(sizeof(Expr));
    *expr.e.BinOp.right = right;

    return expr;
}

Expr Expr_Parenthesized(Expr node)
{
    Expr expr;
    
    expr.type = Parenthesized;

    // Assign the left operand directly
    expr.e.Parenthesized.expr = malloc(sizeof(Expr));
    *expr.e.Parenthesized.expr = node;

    return expr;
}

Expr Parse_BinOp(size_t* i, Token_List* tokens)
{
    Expr left;
    if(tokens->content[*i].type == TOK_OPEN_PARENTHESIS)
    {
        (*i)++;
        left = Expr_Parenthesized(Parse_BinOp(i, tokens));
    }
    else
    {
        left = Expr_Literal(tokens->content[*i]);
    }

    (*i)++;

    while(tokens->content[*i].type == TOK_BINOP)
    {
        BinaryOperators operator = tokens->content[*i].num; // Get the binary operator
        (*i)++;
        
        Expr right;
        if(tokens->content[*i].type == TOK_OPEN_PARENTHESIS)
        {
            (*i)++;
            right = Expr_Parenthesized(Parse_BinOp(i, tokens));
        }
        else
        {
            right = Expr_Literal(tokens->content[*i]);
        }
        // Parse the right operand (another term)
        (*i)++;
        
        // Create a BinOp node and update the left operand
        left = Expr_BinOp(operator, left, right);
    }

    return left;
}

Expr Parse_Tokens(size_t* i, Token_List* tokens)
{
    switch(tokens->content[*i].type)
    {
        case TOK_OPEN_PARENTHESIS:
        {
            (*i)++;
            Expr expr = Parse_BinOp(i, tokens);
            return Expr_Parenthesized(expr);
        }
        break;
        case TOK_NUM:
        {
            switch(tokens->content[(*i)+1].type)
            {
                case TOK_BINOP:
                {
                    Expr binOp = Parse_BinOp(i, tokens);
                    return binOp;
                }
                break;
                default:
                {
                    printf("%d : %zu\n", tokens->content[*i].type, *i);
                    printf("ERROR: Incorrect Syntax!!! ( %d : %zu ) \n", tokens->content[(*i)+1].type, (*i)+1);
                    exit(1);
                }
                break;
            }
        }
        break;
        default:
        {
            printf("TODO: Think about another error message\n");
            printf("%d", tokens->content[*i].type);
            exit(1);
        }
        break;
    }
}

Expr Parse_Program(Token_List* tokens)
{
    Expr expr;
    for(size_t i = 0; i < tokens->size; ++i)
    {
        expr = Parse_Tokens(&i, tokens);
	}
    return expr;
}