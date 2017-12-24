#include <stdio.h>
#include <stdlib.h>


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
    newEdgeHeader->nextEdge = NULL;

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
    edgeNode* current1 = (edgeNode*)malloc(sizeof(edgeNode));
    edgeNode* current2 = (edgeNode*)malloc(sizeof(edgeNode));
    edgeNode* previous1 = NULL;
    edgeNode* previous2 = NULL;

    current1 = v1->edgeHeader;
    current2 = v2->edgeHeader;
    edgeNode* edge1 = newEdge(v2);
    edgeNode* edge2 = newEdge(v1);

    // Handling vertex1
    if (current1->nextEdge == NULL){
        v1->edgeHeader->nextEdge = edge1;
        edge1->nextEdge = NULL;
    }
    else{
        while(current1->nextEdge != NULL){
            previous1 = current1;
            if(current1->nextEdge->refAddress->value > v2->value){
                previous1->nextEdge = edge1;
                edge1->nextEdge = current1;
                break;
            }
            current1 = current1->nextEdge;
        }
  
        previous1->nextEdge = current1;
        current1->nextEdge = edge1;
    }

    // Handling vertex 2
    if (current2->nextEdge == NULL ){
        v2->edgeHeader->nextEdge = edge2;
        edge2->nextEdge = NULL;
    }
    else{
        while(current2->nextEdge != NULL){
            previous2 = current2;
            if(current2->nextEdge->refAddress->value > v1->value){
                previous2->nextEdge = edge2;
                edge2->nextEdge = current2;
                break;
            }
            current2 = current2->nextEdge;
        }
        previous2->nextEdge = current2;
        current2->nextEdge = edge2;
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
            addEdge(sourceVertex,targetVertex);
        }



        else
            perror("One of the vertex node is missing");


    }
    else
        perror("You can't add vertex to its own" );

  

}

void printGraph(Graph* graph){
    vertexNode* temp = (vertexNode*)malloc(sizeof(vertexNode));
    if (graph->header->nextVertex != NULL )
    {
        temp = graph->header->nextVertex;
        if (temp->edgeHeader == NULL)
        {

            while (temp->nextVertex->edgeHeader != NULL){
                printf("%d %s",temp->nextVertex->value,"->");
                temp = temp->nextVertex;
            }
        }

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

void dfsVisit(vertexNode* v){
    while(v->edgeHeader->nextEdge != NULL){

        if (v->edgeHeader->nextEdge->refAddress != NULL){
            if(v->edgeHeader->nextEdge->refAddress->color == 'A'){

                printf("%d \n",v->edgeHeader->nextEdge->refAddress->value);

                v->edgeHeader->nextEdge->refAddress->color = 'B';

                dfsVisit(v->edgeHeader->nextEdge->refAddress);

            }
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
            printf("%d\n",temp->value);
            dfsVisit(temp);
        }
        temp= temp->nextVertex;

    }

}
void print(Graph* graph){
	vertexNode* temp = (vertexNode*) malloc(sizeof(vertexNode));
	edgeNode* edgeTemp = (edgeNode*)malloc(sizeof(edgeNode));
	temp = graph->header->nextVertex;
	edgeTemp = temp->edgeHeader->nextEdge;
	while(temp != NULL){
		printf("%d \n",temp->value );
		// while(edgeTemp != NULL){
		// 	printf("%d ",edgeTemp->refAddress );
		// 	printf("%s\n","->" );
		// 	//edgeTemp = edgeTemp->nextEdge;
		// }
		printf("%s\n"," " );
		temp = temp->nextVertex;
	}
}
int main()
{

    Graph* graph = createGraph();
    addNewVertex(graph,70);
    addNewVertex(graph,71);
    addNewVertex(graph,72);
    addNewVertex(graph,73);
    addNewVertex(graph,74);
    addNewVertex(graph,75);
    addNewVertex(graph,89);

    findAndAdd(graph,70,75);
    findAndAdd(graph,75,73);
    findAndAdd(graph,73,71);
    findAndAdd(graph,71,89);
    findAndAdd(graph,74,70);
    findAndAdd(graph,74,72);
    findAndAdd(graph,74,75);
    print(graph);
    //dfs(graph);
 

    return 0;
}