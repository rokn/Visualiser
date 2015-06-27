
#include "List.h"

#define LINE_LENGTH 100
#define FILE_LENGTH 10000

int main() 
{
	FILE *ifp;
	char *mode = "r";
	char line[LINE_LENGTH];
	char program[FILE_LENGTH];
	char inputFileName[] = "test.c";

	ifp = fopen(inputFileName, mode);

	while (fscanf(ifp, "%s", line) != EOF)
	{
	  	strcat(program,line);
	}

	printf("%s\n", program);

	return 0;
}