#ifndef TREE
#define TREE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct treeNode
{
	char* instrument;
	unsigned short insId;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;


typedef struct tree
{
	TreeNode* root;
} InstrumentTree;



InstrumentTree buildInstrumentTree(FILE* file_instruments, int* size_instruments);
void Insert(InstrumentTree* pt, char* instrument);
TreeNode* FindPlace(TreeNode* t, char* instrument);
int isEmptyTree(InstrumentTree t);
TreeNode* createNewTNode(char* instrument, TreeNode* left, TreeNode* right);
int findInsId(InstrumentTree* tree, char* instrument);
int findInsIdHelper(TreeNode* root, char* instrument);
void freeTree(InstrumentTree* tr);
void freeTreeHelper(TreeNode* root);



#endif // !TREE

