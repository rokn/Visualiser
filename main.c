#include "List.h"
#include "parser.h"

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
	fprintf(ofp, "subgraph variable_int {node[shape=ellipse,color=pink4, label=\"%s\"]; %s; }",assignment,name);
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
	printf("%s\n",name);

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



void AddConnection(char *element1, char *element2)
{
	connections[connectionsCount] = (char*)malloc(sizeof(char[50])); 
	strcat(connections[connectionsCount],element1); 
	strcat(connections[connectionsCount],"->");
	strcat(connections[connectionsCount],element2);
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
	if(result == 0){
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
	Paction action;
	Pvariable variable;
	Pblock *block = NULL;
	char *currBlockName = (char*)malloc(sizeof(char) * 50);
	char *assignment = (char*)malloc(sizeof(char) * 50);
	char *prev = (char*)malloc(sizeof(char) * 50);	
	char *curr = (char*)malloc(sizeof(char) * 50);
	prev = "start";

	int i;

	for (i = 0; i < 5; ++i)
	{
		ListPeekAt(&function.actions, &action, i);

		switch(action)
		{
			case INITVAR:
				ListPeekAt(&function.variables, &variable, 0);
				curr = GraphVarInit(ofp, variable, "main", ListGetSize(&function.variables));
				ListRemoveFront(&function.variables);				
				break;
			case ASSIGNMENT:
				ListPeekAt(&function.assignments, assignment, 0);
				curr = GraphAssignment(ofp,assignment, "main", ListGetSize(&function.assignments));
				ListRemoveFront(&function.assignments);
				break;
			case BLOCK:
				block = (Pblock*)malloc(sizeof(Pblock));
				ListPeekAt(&function.blocks, block, 0);
				curr = currBlockName = GraphBlock(ofp, block, "main",ListGetSize(&function.blocks));
				//ListRemoveFront(&function.variables);
				break;
			case BLOCKEND:
				block = NULL;
				break;
		}

		//printf("%s->%s\n", prev,curr);
		AddConnection(prev,curr);
		prev=curr;
	}
	AddConnection(prev,"end");
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

