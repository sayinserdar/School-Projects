#include <stdio.h>
#include <stdlib.h>
#include  <string.h>

typedef struct graph{

	struct vertexNode *header;
}Graph;

typedef struct vertexNode{

	int value;
	char color;
	struct vertexNode *nextVertex;
	struct edgeNode *edgeHeader;
}vertexNode;

typedef struct edgeNode{

	struct edgeNode *nextEdge;
	struct vertexNode *refAddress;
}edgeNode;

Graph* createGraph()
{
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    vertexNode *header = (vertexNode*) malloc(sizeof(vertexNode));
    graph->header = header;
    header->nextVertex = NULL;
    header->edgeHeader = NULL;
    header->value = -1;
    header->color = 'a';
    return graph;
}
void addNewVertex(Graph* graph,int value){
	vertexNode* newNode = (vertexNode*)malloc(sizeof(vertexNode));
	vertexNode* temp = (vertexNode*)malloc(sizeof(vertexNode));
	temp = graph->header;
	newNode->value = value;
	newNode->color = 'A';
	newNode->nextVertex = NULL;
	newNode->edgeHeader = NULL;

	if (temp->nextVertex == NULL)
	{	
		graph->header->nextVertex = newNode;
	}
	else{
		while(temp->nextVertex != NULL){
			if (temp->nextVertex->value == value)
			{
				break;
			}
			temp = temp->nextVertex;
		}
		temp->nextVertex = newNode;
	}
	

}
edgeNode* newEdge(vertexNode* refNode){
	edgeNode* node = (edgeNode*)malloc(sizeof(edgeNode));
	node->nextEdge = NULL;
	node->refAddress = refNode;
	return node;
}
void addEdge(vertexNode* v1, vertexNode* v2){
	vertexNode* temp1 = (vertexNode*)malloc(sizeof(vertexNode));
	vertexNode* temp2 = (vertexNode*)malloc(sizeof(vertexNode));
	temp1 = v1;
	temp2 = v2;
	edgeNode* edge1 = newEdge(v2);
	edgeNode* edge2 = newEdge(v1);

	// Handling vertex1
	if (temp1->edgeHeader == NULL){
		temp1->edgeHeader = edge1;
	}
	else{
		while(temp1->edgeHeader != NULL){
			temp1->edgeHeader = temp1->edgeHeader->nextEdge;

		}
		temp1->edgeHeader = edge1;
	}
	// Handling vertex 2
	if (temp2->edgeHeader == NULL){
		temp2->edgeHeader = edge2;
	}
	else{
		while(temp2->edgeHeader != NULL){
			temp2->edgeHeader = temp2->edgeHeader->nextEdge;
		}
		temp2->edgeHeader = edge2;
	}

}
void findAndAdd(Graph* graph,int sourceValue,int targetValue){
	vertexNode* sourceVertex = (vertexNode*)malloc(sizeof(vertexNode));
	vertexNode* targetVertex = (vertexNode*)malloc(sizeof(vertexNode));
	sourceVertex = graph->header->nextVertex;
	targetVertex = graph->header->nextVertex;
	int foundSource = 0;
	int foundTarget = 0;

		if (sourceValue != targetValue){
		while(sourceVertex != NULL || sourceVertex->value != sourceValue){
			if (sourceVertex->value == sourceValue){
				foundSource = 1;
				break;
			}
			sourceVertex = sourceVertex->nextVertex;
		}

		while(targetVertex != NULL || targetVertex->value != targetValue){
			if (targetVertex->value == targetValue){
				foundTarget = 1;
				break;
			}
			targetVertex = targetVertex->nextVertex;
		}


		if (foundSource == 1 && foundTarget == 1)
		{	
			//printf("%s %d %s %d \n","foundSource:",foundSource,"foundTarget",foundTarget );
			addEdge(targetVertex,sourceVertex);
		}
		else
		perror("One of the vertex node is missing");
	}
	else
	perror("You can't add vertex to its own" );
	
	printf("%s\n","Succesful" );

}

void printGraphVertex(Graph* graph){
	vertexNode* temp = (vertexNode*)malloc(sizeof(vertexNode));
	if (graph->header->nextVertex != NULL){
		temp = graph->header->nextVertex;
	}
	else{
		printf("%s\n","This graph is empty" );
	}
	while(temp != NULL){
		printf("%d\n",temp->value);
		temp = temp->nextVertex;
	}
}
void printGraphEdge(Graph* graph){
	vertexNode* temp = (vertexNode*)malloc(sizeof(vertexNode));
	if (graph->header->nextVertex != NULL )
	{
		temp = graph->header->nextVertex;
		if (temp->edgeHeader == NULL)
		{
			perror("No edge found");
		}
		else{
			
			while(temp->edgeHeader != NULL){
				//printf("%s %d ","->",temp->edgeHeader->refAddress );
				temp->edgeHeader = temp->edgeHeader->nextEdge;	
			}
			printf("%s\n"," " );
			temp = temp->nextVertex;
		
		}
	}
}
int main()
{
	Graph* graph = createGraph();
 	addNewVertex(graph,3);
 	addNewVertex(graph,5);
 	addNewVertex(graph,6);
 	addNewVertex(graph,67);
 	//printf("%c\n",graph->header->nextVertex->color );
 	printGraphVertex(graph);
 	findAndAdd(graph,3,5);
 	findAndAdd(graph,5,6);
 	findAndAdd(graph,6,67);
 	findAndAdd(graph,3,67);
 	findAndAdd(graph,3,6);
 	findAndAdd(graph,5,67);
 	//printGraphEdge(graph);

    return 0;
}