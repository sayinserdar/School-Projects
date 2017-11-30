// TODO: New node is shown with height 1 but it should be 0
// TODO: I need to check the space character while reading from file
// TODO: BSTDelete function has some problem
// TODO: Memory usage tool ?
// TODO: I need to identify the first sentence with dot
// TODO: Housework 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct Node
{
    char key[30];
    struct Node *left;
    struct Node *right;
    int height;
};
 
int max(int a, int b);
 
// A utility function to get height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
int max(int a, int b)
{
    return (a > b)? a : b;
}
// New node initializer
struct Node* newNode(char key[30])
{
    struct Node* node = (struct Node*)
    malloc(sizeof(struct Node));
    strncpy(node->key,key,strlen(key));
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

// Find the left most value in BST
struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

 
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}
 
// In order to execute rotating functions we need to know whether the difference is higher or equal to 2
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
struct Node* bstInsert(struct Node* node, char key[30]){
    if (node == NULL)
        return(newNode(key));
    
        if (strcmp(key,node->key) < 0){
        node->left  = bstInsert(node->left, key);
        }
        else if (strcmp(key,node->key) > 0){
        node->right = bstInsert(node->right, key);
        }
        else if (strcmp(key,node->key) == 0){
        printf("%s %s \n","This key is already in list",key);

        }
         // Equal keys are not allowed in BST
        return node;
}

 
// Insert function which returns new root of subtree
struct Node* insert(struct Node* node, char key[30])
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
 
    if (strcmp(key,node->key) < 0)
        node->left  = insert(node->left, key);
    else if (strcmp(key,node->key) > 0)
        node->right = insert(node->right, key);
    else if (strcmp(key,node->key) == 0)
    	printf("%s %s \n","This key is already in list",key );
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && strcmp(key,node->left->key) < 0) 
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && strcmp(key,node->right->key) > 0)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && strcmp(key,node->left->key) > 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && strcmp(key,node->right->key) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct Node* deleteNode(struct Node* root, char key[30])
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( strcmp(key,root->key) < 0)
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( strcmp(key,root->key) > 0)
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            printf("%s %s \n","This key is deleted",temp->key );
            free(temp);

        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node* temp = minValueNode(root->right);
 
            // Copy the inorder successor's data to this node
            printf("%s %s \n","This key is deleted",root->key );
            memset(root->key,0,sizeof(root->key));
            strcpy(root->key,temp->key);
            
 
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}
// BST Delete Functions which returns the new node
struct Node* bstDeleteNode(struct Node* root, char key[30])
{
    // If the root is not exist returns root
    if (root == NULL) return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strcmp(key,root->key) < 0)
        root->left = bstDeleteNode(root->left, key);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strcmp(key,root->key) > 0)
        root->right = bstDeleteNode(root->right, key);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            printf("%s %s \n","This key is deleted" ,root->key);
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            printf("%s %s \n","This key is deleted" ,root->key);
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct Node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
         printf("%s %s \n","This key is deleted" ,root->key);
         memset(root->key,0,sizeof(root->key));
         strcpy(root->key,temp->key);
 
        // Delete the inorder successor
        root->right = bstDeleteNode(root->right, temp->key);
    }
    return root;
}

 
// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(struct Node *root){
    if(root != NULL){
        printf("%s \n", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void inOrder(struct Node *root){
	if(root != NULL){
		inOrder(root->left);
		printf("%s\n",root->key);
		inOrder(root->right);
	}
}


 
int main()
{
//clock_t begin = clock();0.000153 0.000122
// 	clock_t end = clock();
// double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  FILE *file;
  double allTime = 0;
  double allTimeAVL = 0;
  clock_t begin;
  clock_t end;
  double time_spent;
  double time_spent_AVL;
  char c;
  char array[50];
  int wordLongCounter = 0;
  file = fopen("Input2.txt", "r");
  struct Node *root = NULL;
  struct Node *rootAVL = NULL;
  if (file) {
    while ((c = getc(file)) != EOF){
    if (c == 32 )
        {
        	begin = clock();
        	root = bstInsert(root,array);
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            allTime = allTime + time_spent;

            begin = clock();
            root = insert(rootAVL,array);
            end = clock();
            time_spent_AVL = (double)(end - begin) / CLOCKS_PER_SEC;
            allTimeAVL = allTimeAVL + time_spent_AVL;

            memset(array, 0, sizeof array);
            wordLongCounter = 0;

        }
        // We just take input as numbers and and letters.
        if(((48<=c)&&(c<=57)) || ((65<=c)&&(c<=90)) || ((97<=c)&&(c<=122))){
         array[wordLongCounter] = (char)c;
        wordLongCounter ++;
        }

    }
    fclose(file);
}
inOrder(root);
root = deleteNode(root,"asdasd");
root = deleteNode(root,"text");
root = deleteNode(root,"text");
root = deleteNode(root,"information");
printf("%s %f\n","Time usage for BST insertions ",allTime );
printf("%s %f\n","Time usage for AVL insertions ",allTimeAVL);

  return 0;
}