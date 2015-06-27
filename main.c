#include "List.h"
#include "parser.h"

int main() 
{
	Pfunction function = ParseFile("test.c");
	int i;
	Pblock block;
	for (i = 0; i < ListGetSize(&function.blocks); ++i)
	{
		ListPeekAt(&function.blocks, &block, i);
		printf("condition : %s\n",block.condition);
	}
	return 0;
}