#include "parser.h"

#define MAX_CONTENT_LENGTH 10000
#define MAX_LINE_LENGTH 1000

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

Ptype isType(char currentToken[50])
{
	if(!strcmp(currentToken, "int"))
	{
		return INT;
	}
	if(!strcmp(currentToken, "double"))
	{
		return DOUBLE;
	}
	if(!strcmp(currentToken, "float"))
	{
		return FLOAT;
	}
	if(!strcmp(currentToken, "char"))
	{
		return CHAR;
	}
	if(!strcmp(currentToken, "long"))
	{
		return LONG;
	}
	return NONE;
}

void resetString(char *str)
{
	memset(str,'\0',sizeof(str));
}

List ParseFile(const char *filename)
{
	bool outsideFunction = true;
	char contents[MAX_CONTENT_LENGTH];
	readFile(filename, contents);
	printf("%s\n", contents);
	List functions;
	ListInit(&functions, sizeof(Pfunction));
	char currentToken[50];
	resetString(currentToken);
	int i;
	Pfunction function;
	Ptype type;
	Pvariable variable;
	for (i = 0; i < strlen(contents); ++i)
	{
		int ch = contents[i];
		strcat(currentToken, &ch);

		if(outsideFunction)
		{
			type = isType(currentToken);

			if(type != NONE)
			{
				function.type = type;
				resetString(function.name);
				int b;

				for (b = 1; contents[i+b]!='('; ++b)
				{
					int ch = contents[i+b];					
					strcat(function.name, &ch);
				}

				if(!strcmp(function.name, "main"))
				{
					function.isMain = true;
				}

				i += b;
				ListInit(&function.arguments, sizeof(Pvariable));
				ListInit(&function.variables, sizeof(Pvariable));
				i++;
				resetString(currentToken);
				
				while(contents[i] != ')')
				{					
					ch = contents[i];
					strcat(currentToken, &ch);

					type = isType(currentToken);

					if(type != NONE)
					{
						variable.type = type;
						for (b = 1; contents[i+b]!=')' && contents[i+b]!=','; ++b)
						{
							int ch = contents[i+b];					
							strcat(variable.name, &ch);
						}

						i+=b;
						ListAdd(&function.arguments, &variable);
						resetString(variable.name);
						resetString(currentToken);
					}

					i++;
				}
				i+=2;
				outsideFunction = false;				
			}
		}
		else
		{
			type = isType(currentToken);
			if(type != NONE)
			{
				variable.type = type;
				for(b = 1; contents[i+b] != ';' || contents[i+b] != '=';b++)
				{
					int ch = content[i+b];
					strcat(variable.name,&ch);
				}
			}
		}
	}

	printf("%d name : %s\n",function.type, function.name);
	// int mainPos = findMain(contents) + 7;

}

// Ptype checkStartOfType(char ch)
// {
// 	switch(ch)
// 	{
// 		case 'i':
// 			return INT;
// 		case 'c':
// 			return CHAR;
// 		case 'f':
// 			return FLOAT;
// 		case 'd':
// 			return DOUBLE;
// 		case 'l':
// 			return LONG;
// 	}
// }

// int findMain(char contents[MAX_CONTENT_LENGTH])
// {
// 	int pos;
// 	char *mainPtr;
// 	mainPtr = strstr(contents,"main");

// 	if(mainPtr!=NULL)
// 	{
// 		pos =  mainPtr - contents;
// 	}
// 	return pos;
// }

// int 

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
