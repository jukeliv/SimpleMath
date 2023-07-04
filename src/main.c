#include "..\include\lexer.h"
#include "..\include\parser.h"
#include "..\include\interpreter.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		// THis ain't V-lang, i am not going to add that you can use features that are not implemented lol
		printf("Usage - sm <INPUT>\n");
		printf("ERROR: No input file passed\n");
		return 1;
	}

    Token_List tokens;
	Token_List_Init(&tokens);

	if(Tokenize_File(&tokens, argv[1]))
        return 1;

	Expr program = Parse_Program(&tokens);

	Token_List_Free(&tokens);

	printf("%f\n", Interpret(program));

	return 0;
}
