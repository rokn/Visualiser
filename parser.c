#include "parser.h"

void readFile(const char *filename, char contents[10000])
{
	FILE *ifp;
	char *mode = "r";
	char line[100];

	ifp = fopen(filename, mode);

	while (fscanf(ifp, "%s", line) != EOF)
	{
	  	strcat(contents,line);
	}
}

List ParseFile(const char *filename)
{
	char contents[10000];
	readFile(filename, contents);
	printf("%s\n", contents);
}