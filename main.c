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
			sprintf(name, "%s_int%d", block,counter); 
			fprintf(ofp, "subgraph variable_int {node[shape=ellipse,color=pink4, label=\"int %s\"]; %s_int%d; }",variable.name, block,counter); 			
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
	connectionsCount++; 
}

int main() 
{

	char *filename = malloc(sizeof(char)*50); 
	printf("Input filename :\n"); 
	scanf("%s",filename); 
	Pfunction function; 
	ParseFile(filename,&function); 
	generateDotFile(function); 
	system("dot -Tpng graph.txt -o graph.png && eog graph.png"); 
	// char assignment[50]; 
	// Pblock block; 
	// ListPeekAt(&function.blocks, &block, 0); 
	// printf("%d\n",block.blockType); 
	// ListPeekAt(&block.assignments, &assignment, 0); 
	// printf("%s\n",assignment); 
	return 0; 
}

void DecodeFunction(FILE *ofp, Pfunction function)
{
	Paction action; 
	Pvariable variable; 
	char *prev = (char*)malloc(sizeof(char) * 50); 
	prev = "start"; 
	ListPeekAt(&function.variables, &variable, 0); 
	char *name = GraphVarInit(ofp,variable, "main", 0); 	
}

void generateDotFile(Pfunction function)
{
	FILE *ofp = fopen("graph.txt", "w"); 
	AddConnection("start","end"); 
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

