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
	struct edgeNode *nextEdge;
}vertexNode;

typedef struct edgeNode{

	struct edgeNode *nextEdge;
	vertexNode *referenceVertex;
}edgeNode;

Graph* createGraph()
{
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    vertexNode *header = (vertexNode*) malloc(sizeof(vertexNode));
    graph->header = header;
    header->nextVertex = NULL;
    header->nextEdge = NULL;
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
	newNode->nextEdge = NULL;

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
	node->referenceVertex = refNode;
	return node;
}
void findVertices(Graph* graph,int sourceValue,int targetValue){
	vertexNode* sourceVertex = (vertexNode*)malloc(sizeof(vertexNode));
	vertexNode* targetVertex = (vertexNode*)malloc(sizeof(vertexNode));
	sourceVertex = graph->header;
	targetVertex = graph->header;
	if (graph != NULL){
		while(sourceVertex->nextVertex != NULL || sourceVertex->nextVertex->value != sourceValue){
			sourceVertex = sourceVertex->nextVertex;
		}
		if (sourceVertex->value == sourceValue)
		{
			while(targetVertex->nextVertex != NULL || targetVertex->nextVertex->value != targetValue){
				targetVertex = targetVertex->nextVertex;
			}
			if (targetVertex->value == targetValue)
			{
				//null kontrolü yok
				edgeNode* sourceEdge = newEdge(targetVertex);
				edgeNode* targetEdge = newEdge(sourceVertex);
				sourceVertex->nextEdge = sourceEdge;
				targetVertex->nextEdge = targetEdge;

			}	
		}

	}
	printf("%s\n","There is no such graph" );

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
		if (temp->nextEdge == NULL)
		{
			/* code */
		}
	}
}
int main()
{
	Graph* graph = createGraph();
 	addNewVertex(graph,3);
 	addNewVertex(graph,5);
 	addNewVertex(graph,67);
 	addNewVertex(graph,6);
 	//printf("%c\n",graph->header->nextVertex->color );
 	printGraphVertex(graph);
 	findVertices(graph,3,6);
    return 0;
}