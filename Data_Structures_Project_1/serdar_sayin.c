#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
struct node {
    char word[100];
    struct node *next;
};
typedef struct node node;

int insert(struct node** headRef, char *word,int arrayLength);
int searchAndCount(node** headRef1,node** headRef2);
int checkMoreThanOne(char word[100],node** headRefResult,int arrayLength);
int search(char word[100],node** headRefResult,int arrayLength);
int searchAndCount2(node** headRef1,node** headRef2);

int main()
{

   
    int c;
    int i=0;
    node *head=NULL;
    node *head1=NULL;
    node *head2=NULL;
    node *head3=NULL;
    int wordLongCounter = 0;
    int wordLongCounter1 = 0;
    int wordLongCounter2 = 0;
    int wordLongCounter3 = 0;
    FILE *file;
    FILE *file1;
    FILE *file2;
    FILE *file3;

    file = fopen("Input2.txt", "r");
    file1 = fopen("Input1.txt", "r");
    file2= fopen("Input2.txt", "r");
    file3 = fopen("Input1.txt", "r");    
    char charArray [100] =" ";
    char charArray1 [100] = " ";
    char charArray2 [100] =" ";
    char charArray3 [100] = " ";
if (file) {
    while ((c = getc(file)) != EOF){
      c = tolower(c);

        if (c == 32 )
        {
            insert(&head,charArray,wordLongCounter);
            memset(charArray, 0, sizeof charArray);
            wordLongCounter = 0;

        }
        // We just take input as numbers and and letters.
        if(((48<=c)&&(c<=57)) || ((65<=c)&&(c<=90)) || ((97<=c)&&(c<=122))){
         charArray[wordLongCounter] = (char)c;
        wordLongCounter ++;
        }
        else{
          
        }   
    }
    fclose(file);
}

if (file1) {
    while ((c = getc(file1)) != EOF){
      c = tolower(c);

        if (c == 32 )
        {         
              insert(&head1,charArray1,wordLongCounter1);
              memset(charArray1, 0, sizeof charArray1);
            wordLongCounter1 = 0; 
        }

        if(((48<=c)&&(c<=57)) || ((65<=c)&&(c<=90)) || ((97<=c)&&(c<=122))){
         charArray1[wordLongCounter1] = (char)c;
        wordLongCounter1 ++;
        }
        else{
          
        }   
    }
    fclose(file1);
}
// MARK: Finding common words among these two linked lists.
int a = searchAndCount(&head1,&head);
printf("%s %d\n","Common words:",a);

// MARK: SECOND PART OF THE HOMEWORK
 if (file2) {
     while ((c = getc(file2)) != EOF) {
       c = tolower(c);
         if (c == 32 )
         {
             insert(&head2,charArray2,wordLongCounter2);
            // printf("%s\n",charArray2);
             memset(charArray2, 0, sizeof charArray2);
             wordLongCounter2 = 0;

         }

         if(((48<=c)&&(c<=57)) || ((65<=c)&&(c<=90)) || ((97<=c)&&(c<=122))){
          charArray2[wordLongCounter2] = (char)c;
         wordLongCounter2 ++;
         }
         else{
           
         }   
     }
     fclose(file2);
}

if (file3) {
     while ((c = getc(file3)) != EOF){
       c = tolower(c);

         if (c == 32 )
         {         
               insert(&head3,charArray3,wordLongCounter3);
               //printf("%s\n",charArray3);
               memset(charArray3, 0, sizeof charArray3);
             wordLongCounter3 = 0; 
         }

         if(((48<=c)&&(c<=57)) || ((65<=c)&&(c<=90)) || ((97<=c)&&(c<=122))){
          charArray3[wordLongCounter3] = (char)c;
         wordLongCounter3 ++;
         }
         else{
           
         }   
     }
     fclose(file3);
 }

 // MARK: Finding common 2-grams among these two linked lists.
 int f = searchAndCount2(&head2,&head3);
 printf("%s %d\n","Common 2-grams:",f );


}



// MARK: Utility Functions
int insert(struct node** headRef, char newWord[100],int arrayLength) {
   struct node* newNode = malloc(sizeof(struct node));
   
     strncpy(newNode->word, newWord,arrayLength);
   newNode->next = *headRef;  
   *headRef = newNode;
   
   if (*headRef == newNode) {
    //Succesful operation
     return 1;  
     }
     else {
      // Operation not succeed   
      return 0;
     }
}
int searchAndCount(node** headRef1,node** headRef2){
  // This variable counts how many matched words among these text files.
  int count = 0;
  int matchFound = 0; 
  int a = 0;
  struct node* tempNode = malloc(sizeof(struct node));
  struct node* counterNode = malloc(sizeof(struct node));

  tempNode = (*headRef2);
  while((*headRef1) != NULL){
    (*headRef2) = tempNode;

    while((*headRef2)!= NULL || a == 1){
      if(strcmp((*headRef1)->word, (*headRef2)->word) == 0 ){
       
        a =checkMoreThanOne((*headRef1)->word,&counterNode,strlen((*headRef1)->word));
      
        if(a == 1){
        count++;
        }
        //Check if the last node's next is not null otherwise assign
        else{

        if ((*headRef2) ->next != NULL){
          (*headRef2) =(*headRef2) ->next;
        }
        else
        break;
        }
      }
      //Word is not matched
      else{
        (*headRef2) = (*headRef2) ->next;
        a = 0;
      }
    }
    
    //Check if the last node's next is not null otherwise assign
    if ((*headRef1) ->next != NULL){
          (*headRef1) =(*headRef1) ->next;
        }
        else
          return count;
     }
    return count;
}
int search(char word[100],node** headRefResult,int arrayLength){
  // This ll contains word returns 1 otherwise 0
  node *myRef=NULL;
  myRef = *headRefResult;
while(myRef != NULL) {
  if (strcmp(myRef->word,word) == 0 )
    return 1;
  //Next node
  myRef = myRef->next;
  }  
return 0;
}

//This function returns 1 if inserting is succesfull otherwise 0
int checkMoreThanOne(char word[100],node** headRefResult,int arrayLength){
  //LL contains word, we cant add this word
  if (search(word,headRefResult,arrayLength) == 1) 
    return 0;
  // Adding word to the Linked list
  else if (search(word,headRefResult,arrayLength) == 0){
    insert(headRefResult,word,arrayLength);
    printf("%s\n",word);
    return 1;
  }
  else{
    return 0;
  }
}
int searchAndCount2(node** headRef1,node** headRef2){
  struct node *counterNode = malloc(sizeof(struct node));
  char array[100];
  char array1[100];
  int count = 0;
  int a = 0;
  struct node* tempNode = malloc(sizeof(struct node));

  tempNode = (*headRef2);
  while((*headRef1) != NULL) {

    (*headRef2) =tempNode;
    memset(array, 0, sizeof array); 
    strcpy(array,(*headRef1)->word);
    strcat(array," ");
    // If Linked lists's next word is not equal to NULL then concate
    if((*headRef1)->next != NULL){
    strcat(array,(*headRef1)->next->word);
    }

    else{
    memset(array, 0, sizeof array);
    }

    while((*headRef2) != NULL || a==1){

    memset(array1, 0, sizeof array1);
    strcpy(array1,(*headRef2)->word);
    strcat(array1," ");
    // If Linked lists's next word is not equal to NULL then concate
    if((*headRef2)->next != NULL){
    strcat(array1,(*headRef2)->next->word);
    }

    else{
    memset(array1, 0, sizeof array); 
    }
    // Did 2-grams match?
    if(strcmp(array,array1) == 0){
      
        // Linked list has this array or not ?
        a = checkMoreThanOne(array,&counterNode,strlen(array));
        // New 2-grams added to linked list
      if ( a== 1)
      {
        count ++;
      }
      //Linked liste atılmadı
      else{
          if ((*headRef2) ->next != NULL){
           // printf("%s\n","If 3" );
          (*headRef2) =(*headRef2) ->next;
        }
        else
        break;
        }
      }
      
      // Passing through next 2-grams
      else{
         if ((*headRef2) ->next != NULL){
          (*headRef2) =(*headRef2) ->next;
          a = 0;
        }
        else
        break;
      }

    }
    
    //Check if the last node's next is not null otherwise assign
    if ((*headRef1) != NULL){
          (*headRef1) =(*headRef1) ->next;
        }
     }
   return count;

}


