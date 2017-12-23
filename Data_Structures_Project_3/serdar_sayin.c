// A C Program to demonstrate adjacency list representation of graphs
 
#include <stdio.h>
#include <stdlib.h>
#include  <string.h>
// A structure to represent an adjacency list node
struct AdjListNode
{
    char color;
    int dest;
    struct AdjListNode* next;

};
 
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->color = 'a';
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjList* currentList = &graph->array[v];
        //printf(" %d %s ", v,"Fake Vertex");
        while (currentList->head)
        {
            printf("-> %d", currentList->head->dest);
            printf("%c",currentList->head->color );
            currentList->head = currentList->head->next;
        }
        printf("\n");
    }
}
  
void readFile(FILE *file){
    int wordLongCounter = 0;
    int c;
    char array[30];
   
     if (file) {
    while ((c = getc(file)) != EOF){
    if (c == 44)
        {
            printf("%s\n",array );
            memset(array, 0, sizeof array);
            wordLongCounter = 0;
        }
        // We just take input as numbers and and letters.
        if (c !=44)
        {
            array[wordLongCounter] = (char)c;
            wordLongCounter ++;
        }
       
        // if(c =='\n'){
        //     printf("%s\n","New line");
        // }
    }
    fclose(file);
   }
}
void bfs(struct Graph* g){
	int i = 0;
	// Her yeni array indexinde bir vertex in tuttugu ona baglı nodelar var.
	// 0 dan başlayıp komşuların hepsine tek tek renk verip sıradaki array indexine geçmem gerek.
	while(i<g->V){
		printf("%s\n", " ");
	while(g->array[i].head != NULL){
	
	printf("%d ",g->array[i].head->dest);
	g->array[i].head = g->array[i].head->next;

	}
	printf("%s\n","Finished first vertex" );
	i++;
	}
}
void dfsVist(struct AdjList u){
    if(u.head->next.color == 'a'){
        u.head->next.color = 'b';
        dfsVisit(u.head->next);
    }
}
void dfs(struct Graph* g){
	int i = 0;
	for (int i = 0; i < g->V; ++i){
        if (g->array[i].head->color == 'a')
        {
            g->array[i].head->color == 'b'
            printf("%s","Header Colored" );
            dfsVist(g->array[i]);      
        }
    i++;
    }
}

// Driver program to test above functions
int main()
{
    int wordLongCounter = 0;
    int c;
    char array[30];
    FILE *file;
    file = fopen("input.txt", "r");
    // create the graph given in above fugure
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
 
    // print the adjacency list representation of the above graph
    
    
    dfs(graph);
    printGraph(graph);
    //bfs(graph);
   // readFile(file);
 
    return 0;
}