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
	IF,
	SWITCH,
	WHILE,
	FOR,
	BLOCKNONE
}PblockType;

typedef struct{
	Ptype type;
	char name[50];
} Pvariable;

typedef struct {
	Ptype type;
	char name[50];
	List arguments;
	List variables;
	List blocks;
	bool isMain;
}Pfunction;

typedef struct{
	PblockType blockType;
	List blocks;
	List variables;
	char condition[100];
}Pblock;

List ParseFile(const char *filename);

#endif