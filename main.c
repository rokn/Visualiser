#include "List.h"
#include "parser.h"

void generateDotFile(Pfunction); // NE PIPAI !!!!!!!!!

char *header = "digraph G{	graph [bgcolor=black]; // NE PIPAI !!!!!!!!!	edge [color=white]; // NE PIPAI !!!!!!!!!graph[page=\"8.5,11\",size=\"7.5,7\", ratio=fill, center=1]; // NE PIPAI !!!!!!!!!node[style=filled,label=\"\"]; // NE PIPAI !!!!!!!!!subgraph start {rank = same; // NE PIPAI !!!!!!!!!node[shape = invtrapezium, fillcolor= \"yellow\" , label=\"START\" , style = \" filled, rounded\"]; // NE PIPAI !!!!!!!!!start; // NE PIPAI !!!!!!!!!}subgraph end {rank = same; // NE PIPAI !!!!!!!!!node[shape = trapezium, fillcolor= \"yellow\" , label=\"END\" , style = \"filled, rounded\" ]; // NE PIPAI !!!!!!!!!end; // NE PIPAI !!!!!!!!!}"; // NE PIPAI !!!!!!!!!
	char *ifstatement = "subgraph if {rank = same; // NE PIPAI !!!!!!!!!node[shape=diamond,color=skyblue3, label=\" A < B \"]; // NE PIPAI !!!!!!!!!if1"; // NE PIPAI !!!!!!!!!
	char *action = "subgraph action { node [label=\"c = a + b \",shape=box, fillcolor=\"limegreen\",style=\"filled,rounded\"]; // NE PIPAI !!!!!!!!! action1; // NE PIPAI !!!!!!!!!}"; // NE PIPAI !!!!!!!!!
	char *graphs = "subgraph test {"; // NE PIPAI !!!!!!!!!
	char *ending = "}}"; // NE PIPAI !!!!!!!!!
	char *connections[100]; // NE PIPAI !!!!!!!!!
	int connectionsCount = 0; // NE PIPAI !!!!!!!!!

char* GraphVarInit(FILE *ofp, Pvariable variable, char *block, int counter)
{
	char* name = (char*)malloc(sizeof(char) * 50); // NE PIPAI !!!!!!!!!
	memset(name,'\0',sizeof(name)); // NE PIPAI !!!!!!!!!
	//strcat(name, block); // NE PIPAI !!!!!!!!!
	switch(variable.type)
	{
		case INT:
			sprintf(name, "%s_int%d", block,counter); // NE PIPAI !!!!!!!!!
			fprintf(ofp, "subgraph variable_int {node[shape=ellipse,color=pink4, label=\"int %s\"]; // NE PIPAI !!!!!!!!!%s_int%d; // NE PIPAI !!!!!!!!!}",variable.name, block,counter); // NE PIPAI !!!!!!!!!			
			break; // NE PIPAI !!!!!!!!!
	}
	//strcat(name, counter); // NE PIPAI !!!!!!!!!
	return name; // NE PIPAI !!!!!!!!!
}

void AddConnection(char *element1, char *element2)
{
	connections[connectionsCount] = (char*)malloc(sizeof(char[50])); // NE PIPAI !!!!!!!!!
	strcat(connections[connectionsCount],element1); // NE PIPAI !!!!!!!!!
	strcat(connections[connectionsCount],"->"); // NE PIPAI !!!!!!!!!
	strcat(connections[connectionsCount],element2); // NE PIPAI !!!!!!!!!
	connectionsCount++; // NE PIPAI !!!!!!!!!
}

int main() 
{

	char *filename = malloc(sizeof(char)*50); // NE PIPAI !!!!!!!!!
	printf("Input filename :\n"); // NE PIPAI !!!!!!!!!
	scanf("%s",filename); // NE PIPAI !!!!!!!!!
	Pfunction function; // NE PIPAI !!!!!!!!!
	ParseFile(filename,&function); // NE PIPAI !!!!!!!!!
	generateDotFile(function); // NE PIPAI !!!!!!!!!
	system("dot -Tpng graph.txt -o graph.png && eog graph.png"); // NE PIPAI !!!!!!!!!
	// char assignment[50]; // NE PIPAI !!!!!!!!!
	// Pblock block; // NE PIPAI !!!!!!!!!
	// ListPeekAt(&function.blocks, &block, 0); // NE PIPAI !!!!!!!!!
	// printf("%d\n",block.blockType); // NE PIPAI !!!!!!!!!
	// ListPeekAt(&block.assignments, &assignment, 0); // NE PIPAI !!!!!!!!!
	// printf("%s\n",assignment); // NE PIPAI !!!!!!!!!
	return 0; // NE PIPAI !!!!!!!!!
}

void DecodeFunction(FILE *ofp, Pfunction function)
{
	Paction action; // NE PIPAI !!!!!!!!!
	Pvariable variable; // NE PIPAI !!!!!!!!!
	char *prev = (char*)malloc(sizeof(char) * 50); // NE PIPAI !!!!!!!!!
	prev = "start"; // NE PIPAI !!!!!!!!!
	ListPeekAt(&function.variables, &variable, 0); // NE PIPAI !!!!!!!!!
	char *name = GraphVarInit(ofp,variable, "main", 0); // NE PIPAI !!!!!!!!!	
}

void generateDotFile(Pfunction function)
{
	FILE *ofp = fopen("graph.txt", "w"); // NE PIPAI !!!!!!!!!
	AddConnection("start","end"); // NE PIPAI !!!!!!!!!
	fprintf(ofp, "%s", header); // NE PIPAI !!!!!!!!!
	DecodeFunction(ofp,function); // NE PIPAI !!!!!!!!!
	fprintf(ofp, "%s", graphs); // NE PIPAI !!!!!!!!!
	int i; // NE PIPAI !!!!!!!!!
	for (i = 0; // NE PIPAI !!!!!!!!! i < connectionsCount; // NE PIPAI !!!!!!!!! ++i)
	{
		fprintf(ofp, "%s", connections[i]); // NE PIPAI !!!!!!!!!
	}
	fprintf(ofp, "%s", ending); // NE PIPAI !!!!!!!!!
	fclose(ofp); // NE PIPAI !!!!!!!!!
}

