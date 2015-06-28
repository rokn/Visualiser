#include "List.h"
#include "parser.h"
#include <stdlib.h>
#include <time.h>

void generateDotFile(Pfunction); 

	char *header = "digraph G{	graph [bgcolor=black]; 	edge [color=white]; graph[page=\"8.5,11\",size=\"7.5,7\", ratio=fill, center=1]; node[style=filled,label=\"\"]; subgraph start {rank = same; node[shape = invtrapezium, fillcolor= \"yellow\" , label=\"START\" , style = \" filled, rounded\"]; start; }subgraph end {rank = same; node[shape = trapezium, fillcolor= \"yellow\" , label=\"END\" , style = \"filled, rounded\" ]; end; }"; 
	char *ifstatement = "subgraph if {rank = same; node[shape=diamond,color=skyblue3, label=\" A < B \"]; if1"; 
	char *action = "subgraph action { node [label=\"c = a + b \",shape=box, fillcolor=\"limegreen\",style=\"filled,rounded\"];  action1; }"; 
	char *graphs = "subgraph test {"; 
	char *ending = "}}"; 
	char *connections[100]; 
	int connectionsCount = 0; 

char* GraphVarInit(FILE *ofp, Pvariable variable, char *block, int counter)
{
	char* name = (char*)malloc(sizeof(char) * 50); 
	memset(name,'\0',sizeof(name)); 
	//strcat(name, block); 
	switch(variable.type)
	{
		case INT:
			sprintf(name, "%s_int%d", block, counter); 
			fprintf(ofp, "subgraph variable_int {node[shape=ellipse,color=pink4, label=\"int %s\"]; %s; }",variable.name, name); 			
			break; 
		case DOUBLE:
			sprintf(name, "%s_double%d", block, counter); 
			fprintf(ofp, "subgraph variable_double {node[shape=ellipse,color=pink4, label=\"double %s\"]; %s; }",variable.name, name); 			
			break; 
		case LONG:
			sprintf(name, "%s_long%d", block, counter); 
			fprintf(ofp, "subgraph variable_long {node[shape=ellipse,color=pink4, label=\"long %s\"]; %s; }",variable.name, name); 			
			break; 
		case FLOAT:
			sprintf(name, "%s_float%d", block, counter); 
			fprintf(ofp, "subgraph variable_float {node[shape=ellipse,color=pink4, label=\"float %s\"]; %s; }",variable.name, name); 			
			break; 
		case CHAR:
			sprintf(name, "%s_char%d", block, counter); 
			fprintf(ofp, "subgraph variable_char {node[shape=ellipse,color=pink4, label=\"char %s\"]; %s; }",variable.name, name); 			
			break; 
	}
	//strcat(name, counter); 
	return name; 
}

char* GraphAssignment(FILE *ofp, char *assignment, char *block, int counter)
{
	char* name = (char*)malloc(sizeof(char) * 50); 
	memset(name,'\0',sizeof(name)); 
	//strcat(name, block); 
	sprintf(name, "%s_assignment%d", block,counter);
	fprintf(ofp, "subgraph action{node[shape=box, fillcolor=\"limegreen\",style=\"filled,rounded\" , label=\"%s\"]; %s}",assignment,name);
	//strcat(name, counter); 
	return name;
}

char* GraphBlock(FILE *ofp, Pblock *blockStructure, char *block, int counter)
{
	char* name = (char*)malloc(sizeof(char) * 50); 
	memset(name,'\0',sizeof(name)); 
	//strcat(name, block); 
	sprintf(name, "%s_block%d", block, counter);
	// printf("%s,%s,%d\n\n",name, block, counter);

	switch(blockStructure->blockType)
	{
		case IF:
			fprintf(ofp, "subgraph if {rank = same; node[shape=diamond,color=skyblue3, label=\"%s\"]; %s;}",blockStructure->condition,name);
			break;
		case ELSE:
			break;
	}

	//strcat(name, counter); 
	return name;
}



void AddConnection(char *element1, char *element2, int ifcolor)
{
	
	connections[connectionsCount] = (char*)malloc(sizeof(char[100]));
	resetString(connections[connectionsCount]);
	strcat(connections[connectionsCount],element1); 
	strcat(connections[connectionsCount],"->");
	strcat(connections[connectionsCount],element2);
	if(ifcolor)
	{
		switch(ifcolor)
		{
			case 1:
				strcat(connections[connectionsCount],"[label = \" true\" , fontcolor = \" green\", color=\"green\"]");
				break;
			case 2:
				strcat(connections[connectionsCount],"[label = \" false\" , fontcolor = \" red\", color=\"red\"]");
				break;
		}
	}
	strcat(connections[connectionsCount],";");	
	connectionsCount++; 
}

int main() 
{
	char *filename = malloc(sizeof(char)*50); 
	printf("Input filename :\n"); 
	scanf("%s",filename); 
	Pfunction function; 
	int result;
	ParseFile(filename,&function, &result); 
	if(result == 0){ //returns if file exists
		generateDotFile(function); 
		system("dot -Tpng graph.txt -o graph.png && eog graph.png"); 
		// char assignment[50]; 
		// Pblock block; 
		// ListPeekAt(&function.blocks, &block, 0); 
		// printf("%d\n",block.blockType); 
		// ListPeekAt(&block.assignments, &assignment, 0); 
	}
	return 0; 
}

void DecodeFunction(FILE *ofp, Pfunction function)
{
	srand(time(NULL));
	Paction action;
	Pvariable variable;
	Pblock *block = NULL;
	bool endBlock=false;
	char *currBlockName = (char*)malloc(sizeof(char) * 50);
	char *assignment = (char*)malloc(sizeof(char) * 50);
	char *prev = (char*)malloc(sizeof(char) * 50);	
	char *curr = (char*)malloc(sizeof(char) * 50);
	currBlockName = "main";
	prev = "start";

	int i,b;

	for (i = 0; i < ListGetSize(&function.actions); ++i)
	{
		ListPeekAt(&function.actions, &action, i);
		switch(action)
		{
			case INITVAR:
				ListPeekAt(&function.variables, &variable, 0);
				curr = GraphVarInit(ofp, variable, "main", ListGetSize(&function.variables));
				ListRemoveFront(&function.variables);
				if(endBlock)
				{
					AddConnection(currBlockName,curr,2);
					endBlock = false;
				}			
				break;
			case ASSIGNMENT:

				ListPeekAt(&function.assignments, assignment, 0);
				curr = GraphAssignment(ofp,assignment, "main", ListGetSize(&function.assignments));
				ListRemoveFront(&function.assignments);
				if(endBlock)
				{
					endBlock = false;
					AddConnection(currBlockName,curr,2);
				}
				break;
			case BLOCK:
				block = (Pblock*)malloc(sizeof(Pblock));
				ListPeekAt(&function.blocks, block, 0);
				curr = GraphBlock(ofp, block, "main",ListGetSize(&function.blocks));
				if(endBlock)
				{
					AddConnection(currBlockName,curr,2);
					endBlock = false;
				}
				currBlockName  = curr;
				printf("curr:%s\n",currBlockName);
				// sprintf(currBlockName,"%d",)

				AddConnection(prev,curr,0);
				prev=curr;
				if(ListGetSize(&block->actions) == 1)
				{
					ListPeekAt(&function.actions, &action, i);		
					switch(action)
					{
						case INITVAR:
							ListPeekAt(&block->variables, &variable, 0);
							curr = GraphVarInit(ofp, variable, currBlockName, ListGetSize(&block->variables));
							ListRemoveFront(&block->variables);				
							break;
						case ASSIGNMENT:
							ListPeekAt(&block->assignments, assignment, 0);
							
							curr = GraphAssignment(ofp,assignment, currBlockName, ListGetSize(&block->assignments));
							ListRemoveFront(&block->assignments);
							break;
						case BLOCK:
							ListPeekAt(&block->assignments, assignment, 0);
							
							curr = GraphAssignment(ofp,assignment, currBlockName, ListGetSize(&block->assignments));
							ListRemoveFront(&block->assignments);
							break;
					}
					AddConnection(prev,curr,1);
					prev=curr;
				}
				else
				{
				for (b = 0; b < ListGetSize(&block->actions); ++b)
				{
					ListPeekAt(&function.actions, &action, i);		
					switch(action)
					{
						case INITVAR:
							ListPeekAt(&block->variables, &variable, 0);
							curr = GraphVarInit(ofp, variable, currBlockName, ListGetSize(&block->variables));
							ListRemoveFront(&block->variables);				
							break;
						case ASSIGNMENT:
							ListPeekAt(&block->assignments, assignment, 0);
							
							curr = GraphAssignment(ofp,assignment, currBlockName, ListGetSize(&block->assignments));
							ListRemoveFront(&block->assignments);
							break;
						case BLOCK:
							ListPeekAt(&block->assignments, assignment, 0);
							
							curr = GraphAssignment(ofp,assignment, currBlockName, ListGetSize(&block->assignments));
							ListRemoveFront(&block->assignments);
							break;
					}
					if(b==0)
					{
						AddConnection(prev,curr,1);
						prev=curr;
						continue;
					}
					if(b < ListGetSize(&block->actions) -1)
					{
						AddConnection(prev,curr,0);
						prev=curr;
					}
				}				
			}
				ListRemoveFront(&function.blocks);
				continue;
				break;
			case BLOCKEND:
				block = NULL;
				endBlock = true;
				break;
		}
		AddConnection(prev,curr,0);
		prev=curr;
	}
	if(endBlock)
	{
		endBlock = false;
		AddConnection(currBlockName,"end",2);
	}
	AddConnection(prev,"end",0);
}

void generateDotFile(Pfunction function)
{
	FILE *ofp = fopen("graph.txt", "w"); 
	fprintf(ofp, "%s", header); 
	DecodeFunction(ofp,function); 
	fprintf(ofp, "%s", graphs); 
	int i; 
	for (i = 0;  i < connectionsCount;  ++i)
	{
		fprintf(ofp, "%s", connections[i]); 
	}
	fprintf(ofp, "%s", ending); 
	fclose(ofp); 
}

