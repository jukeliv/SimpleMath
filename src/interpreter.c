#include "..\include\interpreter.h"

float Interpret(Expr node)
{
    if (node.type == BinOp)
    {
        return Interpret_BinOp(node);
    }
    else if (node.type == Literal)
    {
        return Interpret_Literal(node);
    }
    else if(node.type == Parenthesized)
    {
        return Interpret(*node.e.Parenthesized.expr);
    }

    return 0;
}

float Interpret_Literal(Expr node)
{
    return node.e.Literal.value;
}

float Interpret_BinOp(Expr node)
{
    float left_result = Interpret(*node.e.BinOp.left);
    float right_result = Interpret(*node.e.BinOp.right);

    if (node.e.BinOp.op == BINOP_PLUS)
    {
        return left_result + right_result;
    }
    else if (node.e.BinOp.op == BINOP_MINUS)
    {
        return left_result - right_result;
    }
    else if (node.e.BinOp.op == BINOP_MULTIPLICATION)
    {
        return left_result * right_result;
    }
    else if (node.e.BinOp.op == BINOP_DIVISION)
    {
        return left_result / right_result;
    }

    return 0;
}