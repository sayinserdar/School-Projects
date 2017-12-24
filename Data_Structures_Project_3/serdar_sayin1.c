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
    header->color = 'A';
    return graph;
}
void addNewVertex(Graph* graph,int value){
	vertexNode* newNode = (vertexNode*)malloc(sizeof(vertexNode));
	vertexNode* temp = (vertexNode*)malloc(sizeof(vertexNode));
	edgeNode* newEdgeHeader = (edgeNode*)malloc(sizeof(edgeNode));

	newEdgeHeader->refAddress = NULL;
	newEdgeHeader->nextEdge =NULL;

	temp = graph->header;
	newNode->value = value;
	newNode->color = 'A';
	newNode->nextVertex = NULL;
	newNode->edgeHeader = newEdgeHeader;

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
	edgeNode* temp1 = (edgeNode*)malloc(sizeof(edgeNode));
	edgeNode* temp2 = (edgeNode*)malloc(sizeof(edgeNode));
	temp1 = v1->edgeHeader;
	temp2 = v2->edgeHeader;
	edgeNode* edge1 = newEdge(v2);
	edgeNode* edge2 = newEdge(v1);

	// Handling vertex1
	if (temp1->nextEdge == NULL){
		v1->edgeHeader->nextEdge = edge1;
	}
	else{
		while(temp1->nextEdge != NULL){
			temp1 = temp1->nextEdge;
		}
		temp1->nextEdge = edge1;
	}
	// Handling vertex 2
	if (temp2->nextEdge == NULL){
		v2->edgeHeader->nextEdge = edge2;
	}
	else{
		while(temp2->nextEdge != NULL){
			temp2 = temp2->nextEdge;
		}
		temp2->nextEdge = edge2;
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

void printGraph(Graph* graph){
	vertexNode* temp = (vertexNode*)malloc(sizeof(vertexNode));
	if (graph->header->nextVertex != NULL )
	{
		temp = graph->header->nextVertex;
		if (temp->edgeHeader == NULL)
		{
			perror("No edge found");
		}
		else{


			while(temp!= NULL){
				printf("%d ",temp->value );
			while(temp->edgeHeader->nextEdge != NULL){
				printf("%s %d ","->",temp->edgeHeader->nextEdge->refAddress->value );
				temp->edgeHeader->nextEdge = temp->edgeHeader->nextEdge->nextEdge;
			}
			printf("%s\n"," " );
			temp = temp->nextVertex;

			}
		}
	}
}
// void bfs(Graph* graph,vertexNode *v){
// 	edgeNode* temp = (edgeNode*)malloc(sizeof(edgeNode));
// 	if (graph->header->nextVertex !=NULL){
// 		temp = graph->header->nextVertex->edgeHeader->nextEdge;
// 		while(temp->nextEdge != NULL){
// 		if (temp->refAddress->color == 'A')
// 		{
// 			temp->refAddress->color = 'B';
// 			bfs(graph,temp->refAddress);
// 		}
// 		else
// 		temp = temp->nextEdge;
// 		}
// 	}
// 	else
// 		perror("Bfs with no vertex hmmmm ");

// }
void dfsVisit(vertexNode* v){
	while(v->edgeHeader->nextEdge != NULL){


	if(v->edgeHeader->nextEdge->refAddress->color == 'A'){

		printf("%d %s \n",v->edgeHeader->nextEdge->refAddress->value,"IN DFSVISIT");

        v->edgeHeader->nextEdge->refAddress->color = 'B';

		dfsVisit(v->edgeHeader->nextEdge->refAddress);

	}
        if(v->edgeHeader->nextEdge->nextEdge != NULL)
        v->edgeHeader->nextEdge = v->edgeHeader->nextEdge->nextEdge;

        else
            break;
	}


}

void dfs(Graph* graph){
	vertexNode* temp = (vertexNode*) malloc(sizeof(vertexNode));
	temp = graph->header->nextVertex;
	while(temp != NULL){
	if(temp->color == 'A'){
		temp->color = 'B';
		printf("%d %s \n",temp->value,"IN DFS");
		dfsVisit(temp);
	}
	temp= temp->nextVertex;
}

}
int main()
{


	// if (graph->header->nextVertex !=NULL){
	// 	temp = graph->header->nextVertex;
	// }

	// else
	// 	perror("Dfs with no vertex :) ");
	Graph* graph = createGraph();
 	addNewVertex(graph,70);
 	addNewVertex(graph,71);
 	addNewVertex(graph,72);
 	addNewVertex(graph,73);
 	addNewVertex(graph,74);
 	addNewVertex(graph,75);

 	findAndAdd(graph,74,75);
 	findAndAdd(graph,74,72);
 	findAndAdd(graph,72,70);
 	findAndAdd(graph,70,71);
 	findAndAdd(graph,71,73);
 	findAndAdd(graph,73,75);
 	printGraph(graph);
	//dfs(graph);
 	//printGraph(graph);


 	//dfs(graph,vertexNode* a);

    return 0;
}