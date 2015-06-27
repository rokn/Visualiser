
#include "List.h"

int main() 
{
	FILE *ifp;
	char *mode = "r";
	char line[100];
	char program[10000];
	char inputFileName[] = "test.c";

	ifp = fopen(inputFileName, mode);

	while (fscanf(ifp, "%s", line) != EOF)
	{
	  	strcat(program,line);
	}

	printf("%s\n", program);

	return 0;
}