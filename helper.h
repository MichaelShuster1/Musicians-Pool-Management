#ifndef HELPER
#define HELPER

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <string.h>
#include "List.h"
#include "Tree.h"


#define LINE_SIZE 150
#define IMPORTANT '1'
#define NOT_IMPORTANT '0'
#define ZERO_LETTER '0'
#define NINE_LETTER '9'
#define SEPARATORS " ,.;:?!-\t'()[]{}<>~_"
#define MINUTES_IN_HOUR 60.00


typedef struct musician
{
	char** name;
	bool available;
	MPIList instruments;
}Musician;


typedef struct musician_info
{
	char** name_musician;
	char* name_instrument;
	float price;
}Musician_Info;


typedef struct concert
{
	Date date_of_concert;
	char* name;
	CIList instruments;
	Musician_Info* musicians_info;
}Concert;


typedef struct status
{
	int num_of_availables;
	int size;
}Status;


//musician functions
Musician* CreateMusiciansGroup(int* size, InstrumentTree* tr, FILE* file);
void createNewMusicianName(char** token, char** nexttoken, char* seps, Musician* newmusician, int* logsize);
void createNewMusicianInstrument(InstrumentTree* tr, char** token, char** nexttoken, char* seps, Musician* newmusician);
Musician CreateNewMusician(char* str, InstrumentTree* tr);
Musician*** CreateMusiciansCollection(Musician* MusiciansGroup, int size_instruments, int size_musicians, Status* status_instruments);
Musician** CreateNewMusicianArr(Musician* MusiciansGroup, int insId, int size_musicians,int* logic_size);
bool findIdInList(MPIList* insList, int insId, LNODE** Node);


//sort functions
void SortMusicianCollection(Musician*** MusiciansCollection, Concert* concert, int size_instruments, Status* status_instruments);
bool findInstrument(CIList* inslist, int insId, ConcertInstrument* instrument);
void swapInstruments(MusicianPriceInstrument* data1, MusicianPriceInstrument* data2);
void  SortMusicianArr(Musician** MusicianArr, int size, char importance, int insId);
void adjustMusicianArr(Musician** MusicianArr, int size, int insId);
int cmp_Important(void* var1, void* var2);
int cmp_Not_Important(void* var1, void* var2);


//format functions
Concert* formatConcerts(char** inputconcerts, int size, InstrumentTree* tr);
Concert getConcertDetails(char* str, InstrumentTree* tr);
void concertDetailsSwitch(Concert* newConcert, char* seps, int* index, char** token, InstrumentTree* tr);
void GetConcertName(char** token, char* seps, Concert* newConcert, int* index);
void GetConcertDate(char** token, char* seps, Concert* newConcert, int* index);
void GetConcertHour(char** token, char* seps, Concert* newConcert, int* index);
void GetConcertInstrument(char** token, char* seps, Concert* newConcert, InstrumentTree* tr);


//concert functipns
void ManageConcerts(Musician*** MusicianCollection, Concert* concerts, int num_of_concerts, Status* status_instruments, Musician* MusiciansGroup, int num_of_musicians, int num_of_instruments);
void FindMusiciansForInstrument(Concert* concert, Musician** MusicianArr, int* logic_size, ConcertInstrument data, Status* status_instrument);
int	 getSizeMusicians(Concert* concert);
void printConcert(Concert* concert, int musicians_size);
void printName(char** name);
void printStatusConcert(bool* concert_status, Concert* concert, int musicians_size);
void UpdateAvailables(Musician** MusicianArr, Status* status_instrument);
void ResetAvailables(Musician* MusiciansGroup, int num_of_musicians);
char** getConcertsInput(int* size);


//other
char* GetLineFile(FILE* file);
void checkFileFail(FILE* file);
void checkMemoryFail(void* var);
char* readLine();


//free functions
void freeArr(char** arr);
void freeConcerts(Concert* Concerts, int size);
void freeMusiciansCollection(Musician*** MusiciansCollection, int size_instruments);
void freeMusicianGroup(Musician* arr, int size);



#endif // !HELPER

