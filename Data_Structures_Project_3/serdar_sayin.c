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
    if (current1->nextEdge == NULL || current1->nextEdge->refAddress->value > v2->value){
        edge1->nextEdge = v1->edgeHeader->nextEdge;
        v1->edgeHeader->nextEdge = edge1;
    }
    else{
        while(current1->nextEdge != NULL && current1->nextEdge->refAddress->value < v2->value){
            current1 = current1->nextEdge;
        }
        edge1->nextEdge = current1->nextEdge;
        current1->nextEdge =edge1;
    }

    //Previous Node-> New Node -> Next Node;
    // Handling vertex 2
    if (current2->nextEdge == NULL || current2->nextEdge->refAddress->value > v1->value){
        edge2->nextEdge = v2->edgeHeader->nextEdge;
        v2->edgeHeader->nextEdge = edge2;
    }
    else{
        while(current2->nextEdge != NULL && current2->nextEdge->refAddress->value < v1->value){
            current2 = current2->nextEdge;
        }
        edge2->nextEdge = current2->nextEdge;
        current2->nextEdge =edge2;
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

    printf("%s\n","Succesful" );

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
        printf("%s","Finished?");
        temp= temp->nextVertex;

    }

}
int main()
{

    Graph* graph = createGraph();
    addNewVertex(graph,3);
    addNewVertex(graph,4);
    addNewVertex(graph,5);
    addNewVertex(graph,6);
    addNewVertex(graph,7);
    addNewVertex(graph,8);
    addNewVertex(graph,9);
    addNewVertex(graph,10);


    findAndAdd(graph,3,5);
    findAndAdd(graph,8,4);
    findAndAdd(graph,7,3);
    findAndAdd(graph,10,9);
    findAndAdd(graph,6,8);
    findAndAdd(graph,4,5);
    findAndAdd(graph,6,3);



    dfs(graph);



    //dfs(graph);
    // print(graph);


    //dfs(graph,vertexNode* a);

    return 0;
}