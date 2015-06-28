#include "parser.h"
#include <unistd.h>

#define MAX_CONTENT_LENGTH 10000
#define MAX_LINE_LENGTH 1000
#define TOKEN_MAX 100

int CheckFileExistence(char* filename){
	return access(filename, F_OK) != -1;
}

int readFile(const char *filename, char contents[MAX_CONTENT_LENGTH])
{
	if(CheckFileExistence(filename)){
		FILE *ifp;
		char *mode = "r";
		char line[MAX_LINE_LENGTH];

		ifp = fopen(filename, mode);

		while (fscanf(ifp, "%s", line) != EOF)
		{
	 	  	strcat(contents,line);
		}
		fclose(ifp);
		return 0;
	}
	else{
		printf("File doesn't exist!\n");
		return 1;
	}
}

bool isAssignment(char currentToken[TOKEN_MAX])
{
	if (strstr(currentToken, "=") != NULL && strstr(currentToken, ";") != NULL) 
	{
    	return true;
	}
	return false;
}

Ptype isType(char currentToken[TOKEN_MAX])
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

PblockType isBlock(char currentToken[TOKEN_MAX])
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

Pfunction ParseFile(const char *filename, Pfunction *function,int *result)
{
	bool outsideFunction = true;
	char contents[MAX_CONTENT_LENGTH];
	if(readFile(filename, contents) == 0)
	{
		List functions;
		ListInit(&functions, sizeof(Pfunction));
		char currentToken[TOKEN_MAX];
		resetString(currentToken);
		int i;
		Ptype type;
		Pblock *block = NULL;
		Pvariable variable;
		Paction action;
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
					function->type = type;
					resetString(function->name);

					for (b = 1; contents[i+b]!='('; ++b)
					{
						int ch = contents[i+b];					
						strcat(function->name, &ch);
					}

					if(!strcmp(function->name, "main"))
					{
						function->isMain = true;
					}

					i += b;
					ListInit(&function->arguments, sizeof(Pvariable));
					ListInit(&function->variables, sizeof(Pvariable));
					ListInit(&function->actions, sizeof(Paction));
					ListInit(&function->assignments, sizeof(char[50]));
					ListInit(&function->blocks, sizeof(Pblock));
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
							ListAdd(&function->arguments, &variable);
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
					resetString(variable.name);
					for(b = 1; contents[i+b] != ';' && contents[i+b] != '=';b++)
					{
						int ch = contents[i+b];
						strcat(variable.name,&ch);
					}

					i+=b;
					ListAdd(&function->variables,&variable);
					resetString(currentToken);
					action = INITVAR;
					ListAdd(&function->actions, &action);
					if(contents[i]=='=')
					{
						char assignment[50];
						resetString(assignment);
						strcat(assignment, variable.name);
						strcat(assignment, "=");
						i++;

						while(contents[i]!=';')
						{
							ch = contents[i];
							strcat(assignment, &ch);
							i++;
						}

						ListAdd(&function->assignments,&assignment);
						action = ASSIGNMENT;
						ListAdd(&function->actions, &action);
					}
				}
				else if(blockType != BLOCKNONE)
				{
					i+=2;
					resetString(currentToken);
					block = (Pblock*)malloc(sizeof(Pblock));
					ListInit(&block->variables, sizeof(Pvariable));
					ListInit(&block->actions, sizeof(Paction));
					ListInit(&block->assignments, sizeof(char[50]));
					ListInit(&block->blocks, sizeof(Pblock));
					block->blockType = blockType;

					switch(blockType)
					{
						case IF:						
							while(contents[i] != ')')
							{
								int ch = contents[i];
								strcat(block->condition,&ch);
								i++;
							}						
							action = BLOCK;
							ListAdd(&function->actions, &action);
							break;
					}

					i+=1;
				}
				else if(!strcmp(currentToken,"}"))
				{
					if(block != NULL)
					{
						ListAdd(&function->blocks, block); // <---------------  SHIBAN AMPERSANT 
						action = BLOCKEND;
						ListAdd(&function->actions, &action);
						resetString(block->condition);
						
						resetString(currentToken);
						block = NULL;
					}
					else
					{
						return;
					}
				}
				else if(isAssignment(currentToken))
				{				
					if(block != NULL)
					{
						ListAdd(&block->assignments, &currentToken);					
						action = ASSIGNMENT;
						ListAdd(&block->actions, &action);

					}
					else
					{
						ListAdd(&function->assignments, &currentToken);
						action = ASSIGNMENT;
						ListAdd(&function->actions, &action);
					}

					resetString(currentToken);
				}
			}
			// printf("%s\n", currentToken);
			// if(block != NULL)
			// {
				
			// }
		}
	}

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
