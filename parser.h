#ifndef PARSER
#define PARSER
#include "List.h"

typedef enum {
	INT,
	CHAR,
	FLOAT,
	DOUBLE,
	LONG,
	NONE
}Ptype;

typedef enum {
	INITVAR,
	ASSIGNMENT,
	BLOCK,
	BLOCKEND,
	INPUT,
	OUTPUT,
	NOACTION
}Paction;

typedef enum {
	IF,
	ELSE,
	SWITCH,
	WHILE,
	FOR,
	BLOCKNONE
}PblockType;

typedef struct{
	Ptype type;
	char name[50];
}Pvariable;

typedef struct pblock Pblock;
struct pblock{
	PblockType blockType;
	Pblock *parent;
	List blocks;
	List variables;
	char condition[100];
	List actions;
	List assignments;
};

typedef struct {
	Ptype type;
	char name[50];
	List arguments;
	List variables;
	List blocks;
	List actions;
	List assignments;	
	bool isMain;
}Pfunction;

Pfunction ParseFile(const char *filename,Pfunction*, int*);

#endif