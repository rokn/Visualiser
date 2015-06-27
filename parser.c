#include "parser.h"

#define MAX_CONTENT_LENGTH 10000
#define MAX_LINE_LENGTH 1000

void readFile(const char *filename, char contents[MAX_CONTENT_LENGTH])
{
	FILE *ifp;
	char *mode = "r";
	char line[MAX_LINE_LENGTH];

	ifp = fopen(filename, mode);

	while (fgets(line, MAX_LINE_LENGTH, ifp) != NULL)
	{
	  	strcat(contents,line);
	}
}

List ParseFile(const char *filename)
{
	char contents[MAX_CONTENT_LENGTH];
	readFile(filename, contents);
	printf("%s\n", contents);
}