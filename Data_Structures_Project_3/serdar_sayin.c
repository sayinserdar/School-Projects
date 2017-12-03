#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct vertex{
    int vertexName;
    struct vertex *horizontalVertex;
    struct vertex *verticalVertex;
};

void initVertex(struct vertex *header);
void insertHorizontalVertice(struct vertex *header,int key);
void insertVerticalVertice(struct vertex *header,int key);
int searchVertical(struct vertex *header,int searchKey);
int main() {
    printf("Hello, World!\n");
    struct vertex *temp;
    struct vertex *header = malloc(sizeof(struct vertex)); // *header bir node u gösteriyor ama header tek başına o node un adresini
    initVertex(header);
    insertHorizontalVertice(header,12);
    insertHorizontalVertice(header,45);
    insertHorizontalVertice(header,67);
    insertHorizontalVertice(header,78);
    insertVerticalVertice(header,67);
    insertVerticalVertice(header,43);
    insertVerticalVertice(header,12);
    insertVerticalVertice(header,0);
    insertVerticalVertice(header,9);

    int res = searchVertical(header,0);
    printf("%d",res);
    return 0;

}

void initVertex(struct vertex *header){
    header->vertexName = 0;
    header->verticalVertex = NULL;
    header->horizontalVertex = NULL;
}
void insertHorizontalVertice(struct vertex *header,int key){
    struct vertex *horizontal = malloc(sizeof(struct vertex));
    struct vertex *temp;
    temp = header;
    horizontal->vertexName = key;
    horizontal->horizontalVertex = NULL;
    horizontal->verticalVertex = NULL;
    //List is empty
    if(header == NULL){
        initVertex(header);
    }
    else{
        while (temp->horizontalVertex != NULL){
            temp = temp->horizontalVertex;
        }
        temp->horizontalVertex = horizontal;
    }

}
void insertVerticalVertice(struct vertex *header,int key){
    struct vertex *vertical = malloc(sizeof(struct vertex));
    struct vertex *temp;
    vertical->vertexName = key;
    vertical->verticalVertex = NULL;
    vertical->verticalVertex = NULL;
    //List is empty
    temp = header;
    if(header == NULL){
        initVertex(header);
    }
    else{
        while (temp->verticalVertex != NULL){
            temp = temp->verticalVertex;
        }
        temp->verticalVertex = vertical;
    }
}
int searchVertical(struct vertex *header,int searchKey){
    struct vertex *temp;
    temp = header;
    while (temp !=NULL || (temp->verticalVertex->vertexName == searchKey)){
        if(temp->verticalVertex->vertexName == searchKey){
            printf("%d %s",temp->verticalVertex->vertexName,"is found");
            return 1;
        }
        temp = temp->verticalVertex;
    }

    return 0;
}