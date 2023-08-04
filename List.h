#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
	unsigned short insId;
	float price;
	char* name;

}MusicianPriceInstrument;

typedef struct lnode
{
	MusicianPriceInstrument data;
	struct lnode* next;
}LNODE;

typedef struct mpilist 
{
	LNODE* head;
	LNODE* tail;
}MPIList;


typedef struct date
{
	int day, month, year;
	float hour;
} Date;


typedef struct concertinstrument
{
	int num;
	int inst;
	char importance;
} ConcertInstrument;


typedef struct cnode
{
	ConcertInstrument data;
	struct cnode* next;
} CNODE;


typedef struct cilist
{
	CNODE* head;
	CNODE* tail;
}CIList;





//Musician List
void makeEmptyList(MPIList* lst);
void insertDataToStartList(MPIList* lst, MusicianPriceInstrument data);
void insertNodeToStartList(MPIList* lst, LNODE* head);
LNODE* createNewListNode(MusicianPriceInstrument data, LNODE* next);
bool isEmptyList(MPIList* lst);
void insertDataToEndList(MPIList* lst, MusicianPriceInstrument data);
void insertNodeToEndList(MPIList* lst, LNODE* tail);
void freeList(MPIList* lst);


//Concert List
void makeEmptyCList(CIList* lst);
void insertDataToStartCList(CIList* lst, ConcertInstrument data);
void insertNodeToStartCList(CIList* lst, CNODE* head);
CNODE* createNewCListNode(ConcertInstrument data, CNODE* next);
bool isEmptyCList(CIList* lst);
void insertDataToEndCList(CIList* lst, ConcertInstrument data);
void insertNodeToEndCList(CIList* lst, CNODE* tail);
void freeCList(CIList* lst);


#endif // !LIST
