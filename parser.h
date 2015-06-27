#ifndef PARSER
#define PARSER
#include "List.h"

typedef enum {
	INT,
	CHAR,
	FLOAT,
	DOUBLE,
	LONG
}Ptype;

typedef enum {
	IF,
	SWITCH,
	WHILE,
	FOR
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
}Pfunction;

typedef struct{
	PblockType blockType;
	List blocks;
}Pblock;

List ParseFile(const char *filename);

#endif