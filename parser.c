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

PblockType isBlock(char currentToken[50])
{
	if(!strcmp(currentToken, "if"))
	{
		return IF;
	}
	if(!strcmp(currentToken, "for"))
	{
		return FOR;
	}
	if(!strcmp(currentToken, "while"))
	{
		return WHILE;
	}
	if(!strcmp(currentToken, "switch"))
	{
		return SWITCH;
	}
	return BLOCKNONE;
}

void resetString(char *str)
{
	memset(str,'\0',sizeof(str));
}

Pfunction ParseFile(const char *filename)
{
	bool outsideFunction = true;
	char contents[MAX_CONTENT_LENGTH];
	readFile(filename, contents);
	List functions;
	ListInit(&functions, sizeof(Pfunction));
	char currentToken[100];
	resetString(currentToken);
	int i;
	Pfunction function;
	Ptype type;
	Pblock block;
	Pvariable variable;
	for (i = 0; i < strlen(contents); ++i)
	{
		int ch = contents[i];
		strcat(currentToken, &ch);
		type = isType(currentToken);
		int b;
		if(outsideFunction)
		{
			if(type != NONE)
			{
				function.type = type;
				resetString(function.name);

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
				ListInit(&function.blocks, sizeof(Pblock));
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
				resetString(currentToken);
				i+=1;
				outsideFunction = false;				
			}
		}
		else
		{
			PblockType blockType = isBlock(currentToken);
			if(type != NONE)
			{
				variable.type = type;
				for(b = 1; contents[i+b] != ';' && contents[i+b] != '=';b++)
				{
					int ch = contents[i+b];
					strcat(variable.name,&ch);
				}
				i+=b;
				ListAdd(&function.variables,&variable);
				resetString(currentToken);

			}
			else if(blockType != BLOCKNONE)
			{
				i+=2;
				resetString(currentToken);
				switch(blockType)
				{
					case IF:
						block.blockType = blockType;
						while(contents[i] != ')')
						{
							int ch = contents[i];
							strcat(block.condition,&ch);
							i++;
						}
						ListAdd(&function.blocks, &block);
						resetString(block.condition);
						break;
				}
				i+=1;
			}
		}
	}

	// int mainPos = findMain(contents) + 7;
	return function;
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
