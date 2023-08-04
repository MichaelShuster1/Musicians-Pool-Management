#include "List.h"


//Musician List functions

//This function creates an empty list
void makeEmptyList(MPIList* lst)
{
	lst->head = lst->tail = NULL;
}


//This function inserts data into the start of the list
void insertDataToStartList(MPIList* lst, MusicianPriceInstrument data)
{
	LNODE* newHead;
	newHead = createNewListNode(data, NULL);
	insertNodeToStartList(lst, newHead);
}


//This function creates a new list node (by allocating memory)
LNODE* createNewListNode(MusicianPriceInstrument data, LNODE* next)
{
	LNODE* res;
	res = (LNODE*)malloc(sizeof(LNODE));
	checkMemoryFail(res);
	res->data = data;
	res->next = next;
	return res;
}


//This function inserts a list node into the start of a list
void insertNodeToStartList(MPIList* lst, LNODE* head)
{
	if (isEmptyList(lst) == true)
	{
		head->next = NULL;
		lst->head = lst->tail = head;
	}
	else
	{
		head->next = lst->head;
		lst->head = head;
	}
}


//This function checks if a list is empty, returns true or false
bool isEmptyList(MPIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}


//This function inserts data into the end of a list
void insertDataToEndList(MPIList* lst, MusicianPriceInstrument data)
{
	LNODE* newTail;
	newTail = createNewListNode(data, NULL);
	insertNodeToEndList(lst, newTail);
}

//This function inserts a node into the end of a list
void insertNodeToEndList(MPIList* lst, LNODE* tail)
{
	if (isEmptyList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

//This function frees the allocated memory of a list
void freeList(MPIList* lst)
{
	LNODE* curr = lst->head;
	LNODE* saver;

	while (curr != NULL)
	{
		saver = curr->next;
		free(curr->data.name);
		free(curr);
		curr = saver;
	}
}



//Concert List functions

//This function creates an empty list
void makeEmptyCList(CIList* lst)
{
	lst->head = lst->tail = NULL;
}


//This function inserts data into the start of the list
void insertDataToStartCList(CIList* lst, ConcertInstrument data)
{
	CNODE* newHead;
	newHead = createNewCListNode(data, NULL);
	insertNodeToStartCList(lst, newHead);
}


//This function creates a new list node (by allocating memory)
CNODE* createNewCListNode(ConcertInstrument data, CNODE* next)
{
	CNODE* res;
	res = (CNODE*)malloc(sizeof(CNODE));
	checkMemoryFail(res);
	res->data = data;
	res->next = next;
	return res;
}


//This function inserts a list node into the start of a list
void insertNodeToStartCList(CIList* lst, CNODE* head)
{
	if (isEmptyCList(lst) == true)
	{
		head->next = NULL;
		lst->head = lst->tail = head;
	}
	else
	{
		head->next = lst->head;
		lst->head = head;
	}
}


//This function checks if a list is empty, returns true or false
bool isEmptyCList(CIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}


//This function inserts data into the end of a list
void insertDataToEndCList(CIList* lst, ConcertInstrument data)
{
	CNODE* newTail;
	newTail = createNewCListNode(data, NULL);
	insertNodeToEndCList(lst, newTail);
}


//This function inserts a node into the end of a list
void insertNodeToEndCList(CIList* lst, CNODE* tail)
{
	if (isEmptyCList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}


//This function frees the allocated memory of a list
void freeCList(CIList* lst)
{
	CNODE* curr = lst->head;
	CNODE* saver;

	while (curr != NULL)
	{
		saver = curr->next;
		free(curr);
		curr = saver;
	}
}
