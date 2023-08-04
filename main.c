/*
* Michael Shuster, 209516210
* Igal Kaminski , 208853564
* 
* The program manages the musicians collection for the given concerts of the user
*/


#include "helper.h"


void main(int argc, char* argv[])
{
	FILE* file_instruments,*file_musicians;
	InstrumentTree tr;
	Musician* MusiciansGroup;
	Musician*** MusiciansCollection;
	Status* status_instruments;
	Concert* concerts;
	char **input_concerts;
	int size_instruments,size_musicians, num_of_concerts = 0;


	file_instruments = fopen(argv[1], "r");
	checkFileFail(file_instruments);

	tr = buildInstrumentTree(file_instruments, &size_instruments);
	fclose(file_instruments);

	file_musicians = fopen(argv[2], "r");
	checkFileFail(file_musicians);

	MusiciansGroup = CreateMusiciansGroup(&size_musicians, &tr, file_musicians);
	fclose(file_musicians);

	
	status_instruments = (Status*)malloc(sizeof(Status) * size_instruments);
	checkMemoryFail(status_instruments);
	MusiciansCollection = CreateMusiciansCollection(MusiciansGroup, size_instruments, size_musicians,status_instruments);
	input_concerts = getConcertsInput(&num_of_concerts);
	concerts = formatConcerts(input_concerts, num_of_concerts,&tr);
	ManageConcerts(MusiciansCollection, concerts, num_of_concerts, status_instruments, MusiciansGroup,size_musicians,size_instruments);


	//freeing all the allocated memory of the program
	freeTree(&tr);
	freeArr(input_concerts);
	freeMusicianGroup(MusiciansGroup,size_musicians);
	freeMusiciansCollection(MusiciansCollection, size_instruments);
	freeConcerts(concerts, num_of_concerts);
	free(status_instruments);

}






























