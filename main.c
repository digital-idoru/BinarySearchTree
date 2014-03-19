/*************************************************************************
Daniel S. Hono II
Simple Binary Search Tree implementation for handling strings.
Includes an implementation of Depth First Search for traversing the tree. 
************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef DEFINES
#define DEFINES

#define INFILE 1 //Input file has argument 1 
#define OUTFILE 2 //Output file has argument 2 
#define CMD_ARGC 3 //Correct number of command line arguments 
#define STR_LEN 15 //Max string length for this project 

#endif

/* Structure definition to for binary tree node */
struct tNode {
  char str[STR_LEN];
  struct tNode* left;
  struct tNode* right;
};


void insert(char*, struct tNode**); //insert string into the binary search tree. Input file is assumed to have all distinct stings. 
struct tNode* createNode(char*); //create a node to insert into the binary search tree. 
void printTree(struct tNode*); //Print the tree using depth-first search prefering left branches. 
int height(struct tNode*, int); //Compute the height of a binary search tree. 
int numberLeaves(struct tNode*, int); //Compute the number of leaves in a binary search tree.
void stringCount(struct tNode*, int*); //Count the number of strings (nodes) in this binary tree. 

//Macro functions defined here
#define MAX(A,B) (A > B ? A : B) 


int main(int argc, const char* argv[]) {

	//File pointers for the input and output files. 
	FILE* in; 
	FILE* out; 
  
	//root of the tree
	struct tNode* root = NULL;

	//Buffer for reading the string from the file. 
	char sBuffer[STR_LEN];
  
	//Counters for information about the tree
	int numberStrings = 0;
	int treeHeight = 0;
	int leaves = 0;
	int leftHeight = 0;
	int rightHeight = 0;
	int leftStrings = 0;
	int rightStrings = 0;

	//Needs infile and outfile for proper usage
	if(argc != CMD_ARGC) {
		fprintf(stderr, "Error - Usage.\n");
		exit(EXIT_FAILURE);
	}

	//Open the infile, exit if cannot be opened
	if( (in = fopen(argv[INFILE], "r")) == NULL) {
		fprintf(stderr, "Error - %s could not be opened.\n", argv[INFILE]);
		exit(EXIT_FAILURE);
	}
  
	//Open the outfile for writting
	if ((out = fopen(argv[OUTFILE], "w")) == NULL) {
		fprintf(stderr, "Error - %s could not be opened for writting.\n", argv[OUTFILE]);
		exit(EXIT_FAILURE);
	}

	//Read the strings from the input file
	while(fscanf(in,"%s",sBuffer) != EOF) {
		insert(sBuffer, &root);
		numberStrings++;
	}

	//DEBUG Function to print the strings out in a depth first search 
	printTree(root);

	//Functions to compute the desired stats about the tree. 
	treeHeight = height(root,0);
	leftHeight = height(root->left,0);
	rightHeight = height(root->right,0);
	leaves = numberLeaves(root, 0);
	stringCount(root->left, &leftStrings);
	stringCount(root->right, &rightStrings);

	//Print the results. 
	fprintf(out,"No. strings = %d\n", numberStrings);
	fprintf(out,"Height of the tree = %d\n", treeHeight);
	fprintf(out,"No. Leaves in tree = %d\n", leaves);
	fprintf(out,"Height of the left sub-tree = %d\n", leftHeight);
	fprintf(out,"No. strings left sub-tree = %d\n", leftStrings);
	fprintf(out,"Height of the right sub-tree = %d\n", rightHeight);
	fprintf(out,"No. strings right sub-tree = %d\n", rightStrings);

	return 0;
}


//Recursively build up the tree from the input string
void insert(char* sBuffer, struct tNode** probe) {

  if(*probe == NULL) {
    *probe = createNode(sBuffer);
    return;
  } else {
    if(strcmp(sBuffer, (*probe)->str) > 0) {
      probe = &((*probe)->right);
      insert(sBuffer, probe);
    } else {
      probe = &((*probe)->left); 
      insert(sBuffer, probe);
    }
  }

  return;
}


//Function to create a new node. 
struct tNode* createNode(char* sBuffer) {
  
  struct tNode* node = (struct tNode*)malloc(sizeof(struct tNode));
  if (node == NULL) {
	  fprintf(stderr, "Could not allocate space for new BST node!"); exit(EXIT_FAILURE);
  }

  node->left = NULL;
  node->right = NULL;
  strcpy(node->str, sBuffer);

  return node;
}


//Depth first search for nodes to print them
//Nodes to be visited are implicitly stored on the stack 
void printTree(struct tNode* probe) {

  if(probe == NULL) {
    return;
  } else {

    printf("NODE: %s\n", probe->str);

    if(probe->left != NULL) {
      printTree(probe->left);
    } 

    if(probe->right != NULL) {
      printTree(probe->right);
    }

    return;
  }
}

//Recursively find the height of the tree. 
int height(struct tNode* probe, int treeHeight) {

  if((probe != NULL) && (probe->left == NULL) && (probe->right == NULL)) {
    return 0; 
  }
  
  if(probe != NULL) {
    treeHeight = 1 + (MAX(height(probe->left,treeHeight), height(probe->right,treeHeight)));
  }

 return treeHeight;
 }

/*Find the number of leaves in the tree */
int numberLeaves(struct tNode* probe, int cLeaves) {

  if(probe != NULL) {
    if((probe->left == NULL) && (probe->right == NULL)) {
      return 1;
    }
  } 
  if(probe != NULL) {
    cLeaves += (numberLeaves(probe->right, cLeaves) + numberLeaves(probe->left, cLeaves));
  }
  return cLeaves;
}

/*Count the number of strings in the tree */
void stringCount(struct tNode* probe, int *strings) {
 
  if(probe == NULL) {
    return;
  } else {

    (*strings)++;
    if(probe->left != NULL) {
      stringCount(probe->left, strings);
    }
    if(probe->right != NULL) {
      stringCount(probe->right, strings);
    }
  }
  return;
}
