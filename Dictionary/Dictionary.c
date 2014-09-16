// April Dawn Kester
// akester
// CMPS 12m
// August 7, 2013
// Creates Dictionary using LinkedList operations
// Dictionary.c
// No special instructions

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"


// private types --------------------------------------------------------------

// NodeObj
typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor of the Node type
Node newNode(char* k, char* v) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->key = k;
   N->value = v;
   N->next = NULL;
   return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// DictionaryObj
typedef struct DictionaryObj{
   Node head;
   int numItems;
} DictionaryObj;


// private helper functions --------------------------------------------------

//findKey()
//returns a reference to the NodeObj containing its argument key or return null if no such NodeObj exists
Node findKey(Node H, char* targetKey){
  /* for(int i = 0; i<D->numItems; N=N->next){
    if(strcmp(N->key, targetKey)==0){
	return N;
    }
  }
  return NULL;*/
 
while(H != NULL){
    if(strcmp(H->key, targetKey)==0){
      break;
    }
    H = H->next;
    }
    return H;
}

//myString()
void myString(FILE* out, Node H){
  if(H!=NULL){
    myString(out, H->next);
    fprintf(out, "%s %s\n", H->key, H->value);
  }
}

//deleteAll
void deleteAll(Node N){
  if (N!=NULL){
    deleteAll(N->next);
    freeNode(&N);
  }
}


// public functions -----------------------------------------------------------

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(void){
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D!=NULL);
   D->head = NULL;
   D->numItems = 0;
   return D;
}

// Dictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
      if( !isEmpty(*pD) ) makeEmpty(*pD);
      free(*pD);
      *pD = NULL;
   }
}

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, 
              "DICTIONARY Error: calling isEmpty() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return(D->numItems==0);
}

//size()
// returns the number of (key, value) pairs in D
// pre none
int size(Dictionary D){
  return D->numItems;
}

// lookup()
// returns the value v such that (k,v) is in D, or returns NULL if no such value v exists
// pre: none
char* lookup(Dictionary D, char* k){
  Node N = findKey(D->head, k);
  if(N==NULL){
    return NULL;
  }
  else{
    return N->value;
  }
}

// insert()
// inserts new (key, value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v){
  Node N;  
  if(findKey(D->head, k)!=NULL){
    fprintf(stderr, "DICTIONARY Error: calling insert() when key already exists\n");
    exit(EXIT_FAILURE);
  }
  N = newNode(k, v);
  N->next = D->head;
  D->head = N;
  N = NULL;
  D->numItems++;
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k){
  Node N;
  if(findKey(D->head, k)==NULL){
    fprintf(stderr, "Dictionary Error: calling delete() on Empty Dictionary\n");
    exit(EXIT_FAILURE);
  }
  if(findKey(D->head, k)==D->head){
    N = D->head;
    D->head = D->head->next;
    N->next = NULL;
  }else{
    N = findKey(D->head, k);
    Node prev = D->head;
    Node temp = D->head->next;
    while(temp !=N){
      temp = temp->next;
      prev = prev->next;
    }
    prev->next = N->next;
    N->next = NULL;
  }
  D->numItems--;
  freeNode(&N);

}

// makeEmpty()
// resets D to the empty state
// pre: !isEmpty(D)
void makeEmpty(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, 
              "DICTIONARY Error: calling makeEmpty() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if( D->numItems==0 ){
      fprintf(stderr, "DICTIONARY Error: calling makeEmpty() on empty Dictionary\n");
      exit(EXIT_FAILURE);
   }
   deleteAll(D->head);
   D->head = NULL;
   D->numItems = 0;
}

// printDictionary()
// prints a text representation of D to the file pointed to by out
// pre: none
void printDictionary(FILE* out, Dictionary D){
  //  Node N;
   if( D==NULL ){
      fprintf(stderr, 
              "DICTIONARY Error: calling printDictionary() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   myString(out, D->head);
   /* for(N=D->head; N!=NULL; N=N->next){
     fprintf(out, "%s %s\n",  N->key, N->value);
     }*/
}


