#include "Tree.h"



/*
the function gets a file and a pointer to size of the instruments
and then the function builds the tree with given file 
and returns the size of the instruments with given pointer
*/
InstrumentTree buildInstrumentTree(FILE* file_instruments, int* size_instruments)
{
	int size = 0;
	char* curr_line;
	InstrumentTree tr;
	tr.root = NULL;

	curr_line = GetLineFile(file_instruments);
	while (curr_line)
	{
		size++;
		Insert(&tr, curr_line);//inserts the current instrument to the tree
		curr_line = GetLineFile(file_instruments);
	}

	*size_instruments = size;
	return tr;
}



/*
the function gets a tree and a name of the instrument.
the function inserts a new node with the given name to the given tree
*/
void Insert(InstrumentTree* pt, char* instrument)
{
	TreeNode* father;
	TreeNode* new_one;


	new_one = createNewTNode(instrument, NULL, NULL);

	if (isEmptyTree(*pt))
		pt->root = new_one;
	else
	{
		father = FindPlace(pt->root, instrument);
		if (strcmp(father->instrument, instrument) > 0)
			father->left = new_one;
		else
			father->right = new_one;
	}
}


/* Returning the parent of the new instrument's name needed to be inserted */
TreeNode* FindPlace(TreeNode* t, char* instrument)
{
	if (strcmp(t->instrument, instrument) > 0)
	{
		if (t->left == NULL)
			return t;
		else
			return FindPlace(t->left, instrument);
	}
	else
	{
		if (t->right == NULL)
			return t;
		else
			return FindPlace(t->right, instrument);
	}
}


/* Checking if the tree is empty */
int isEmptyTree(InstrumentTree t)
{
	return (t.root == NULL);
}


/*the functtion creates a new Tree node with given instrument's name and the given left and right child nodes*/
TreeNode* createNewTNode(char* instrument, TreeNode* left, TreeNode* right)
{
	static int insID = 0;//the id of the instrument
	TreeNode* res;
	res = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryFail(res);
	res->instrument = instrument;
	res->insId = insID;
	insID++;
	res->left = left;
	res->right = right;
	return res;
}


/*
the functions calls the findInsIdHelper function with the root of the tree 
and returns the return value of the called function
*/
int findInsId(InstrumentTree* tree, char* instrument)
{
	return findInsIdHelper(tree->root, instrument);
}


/*
the function returns the id of the given instrument in the given tree
if the instrument not found in the given tree the the function returns -1
*/
int findInsIdHelper(TreeNode* root, char* instrument)
{
	int res = -1;
	if (root == NULL)
	{
		return res;
	}

	int lexOrder = strcmp(root->instrument, instrument);
	if (lexOrder < 0)
	{
		res = findInsIdHelper(root->right, instrument);
	}
	else if (lexOrder > 0)
	{
		res = findInsIdHelper(root->left, instrument);
	}
	else
	{
		return root->insId;
	}
}


/*the functions calls the freeTreeHelper function with the root of the tree*/
void freeTree(InstrumentTree* tr)
{
	freeTreeHelper(tr->root);
}


/*the function frees the memory of all the nodes and their data in the given tree*/
void freeTreeHelper(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		freeTreeHelper(root->left);
		freeTreeHelper(root->right);
		free(root->instrument);
		free(root);
	}
}