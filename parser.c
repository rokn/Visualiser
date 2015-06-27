#include "parser.h"

#define MAX_CONTENT_LENGTH 10000
#define MAX_LINE_LENGTH 100

void readFile(const char *filename, char contents[MAX_CONTENT_LENGTH])
{
	FILE *ifp;
	char *mode = "r";
	char line[MAX_LINE_LENGTH];

	ifp = fopen(filename, mode);

	while (fscanf(ifp, "%s", line) != EOF)
	{
	  	strcat(contents,line);
	}
}

List ParseFile(const char *filename)
{
	char contents[MAX_CONTENT_LENGTH];
	readFile(filename, contents);
	printf("%s\n", contents);
	int mainPos = findMain(contents) + 7;

}

Ptype checkStartOfType(char ch)
{
	switch(ch)
	{
		case 'i':
			return INT;
		case 'c':
			return CHAR;
		case 'f':
			return FLOAT;
		case 'd':
			return DOUBLE;
		case 'l':
			return LONG;
	}
}

int findMain(char contents[MAX_CONTENT_LENGTH])
{
	int pos;
	char *mainPtr;
	mainPtr = strstr(contents,"main");

	if(mainPtr!=NULL)
	{
		pos =  mainPtr - contents;
	}
	return pos;
}

// Ptype expected = checkStartOfType(contents[i]);

// 		switch(expected)
// 		{
// 			case INT:
// 				if(contents[i+1] == 'n' && contents[i+2] == 't')
// 			case CHAR:
// 				return CHAR;
// 			case FLOAT:
// 				return FLOAT;
// 			case DOUBLE:
// 				return DOUBLE;
// 			case LONG:
// 				return LONG;
// 		}