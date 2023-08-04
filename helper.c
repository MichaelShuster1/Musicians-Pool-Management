#include "helper.h"


/*This function checks if a file was opened successfully*/
void checkFileFail(FILE* file)
{
	if (file == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		exit(1);
	}
}


/*This function frees the allocated memory of an array of strings*/
void freeArr(char** arr)
{
	int i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}


/*This function checks if a memory allocation was successful*/
void checkMemoryFail(void* var)
{
	if (var == NULL)
	{
		printf("memory error!");
		exit(1);
	}
}


/*
This function gets an instruments tree, a file and a pointer to size
The function will create an array of musicians from the file, and return it. the function also updates the number of musicians by reference
*/
Musician* CreateMusiciansGroup(int* size, InstrumentTree* tr, FILE* file)
{
	int physize = 1, logsize = 0;
	Musician* MusiciansGroup = (Musician*)malloc(sizeof(Musician));
	checkMemoryFail(MusiciansGroup);
	char* musician;

	musician = GetLineFile(file);
	while (musician != NULL)
	{
		if (logsize >= physize)
		{
			physize *= 2;
			MusiciansGroup = (Musician*)realloc(MusiciansGroup, sizeof(Musician) * physize);
			checkMemoryFail(MusiciansGroup);
		}
		MusiciansGroup[logsize] = CreateNewMusician(musician, tr);//Creates a single new musician
		logsize++;
		free(musician);
		musician = GetLineFile(file);
	}

	MusiciansGroup = (Musician*)realloc(MusiciansGroup, sizeof(Musician) * logsize);
	checkMemoryFail(MusiciansGroup);
	*size = logsize;
	return MusiciansGroup;
}


/*
This function gets and instruments tree, instruments name and price, a musician and seps
The function adds the instrument to the list of instruments the musician have (if the instrument exists in the tree) and advances to the next instrument
*/
void createNewMusicianInstrument(InstrumentTree* tr, char** token, char** nexttoken, char* seps, Musician* newmusician)
{

	MusicianPriceInstrument data;

	int insID = findInsId(tr, *token); //finds instruments id in the tree (if it exists)
	if (insID != -1)
	{
		data.insId = insID;
		data.name = strdup(*token);
		checkMemoryFail(data.name);
		sscanf(*nexttoken, "%f", &(data.price));
		insertDataToEndList(&(newmusician->instruments), data);
	}

	*token = strtok(NULL, seps);
	if (*token != NULL)
	{
		*nexttoken = strtok(NULL, seps);
	}
	else
	{
		*nexttoken = NULL;
	}


}


/*This function creates a single word in a musicians name*/
void createNewMusicianName(char** token, char** nexttoken, char* seps, Musician* newmusician, int* logsize)
{
	int len = strlen(*token);
	newmusician->name[*logsize] = (char*)malloc(sizeof(char) * (len + 1));
	checkMemoryFail(newmusician->name[*logsize]);
	sscanf(*token, "%s", newmusician->name[*logsize]);
	(*logsize)++;
	*token = *nexttoken;
	*nexttoken = strtok(NULL, seps);
}


/*This function creates a single musiciansand returns it*/
Musician CreateNewMusician(char* str, InstrumentTree* tr)
{
	Musician newmusician;
	char seps[] = SEPARATORS;
	char* token;
	char* nexttoken;
	int logsize = 0, physize = 1;
	makeEmptyList(&(newmusician.instruments));
	newmusician.available = true;

	newmusician.name = (char**)malloc(sizeof(char*));//allocate memory for musician's name
	checkMemoryFail(newmusician.name);
	token = strtok(str, seps);//get first token
	nexttoken = strtok(NULL, seps);//get second token

	while (nexttoken != NULL)
	{

		if (nexttoken[0] >= ZERO_LETTER && nexttoken[0] <= NINE_LETTER)//check if the tokens are on an instrument 
		{
			createNewMusicianInstrument(tr, &token, &nexttoken, seps, &newmusician);
		}
		else// the tokens are on a name
		{
			if (logsize >= physize)
			{
				newmusician.name = (char**)realloc(newmusician.name, sizeof(char*) * (physize * 2));
				checkMemoryFail(newmusician.name);
				physize = physize * 2;
			}

			createNewMusicianName(&token, &nexttoken, seps, &newmusician, &logsize);

		}
	}

	newmusician.name = (char**)realloc(newmusician.name, sizeof(char*) * (logsize + 1));
	checkMemoryFail(newmusician.name);
	newmusician.name[logsize] = NULL;

	return newmusician;
}



/*
the function creates and returns a new musician collection array with the given musician group
in way that in the element i of the array will be a array of pointers to the musicians that plays
on instrument with the id i.
*/
Musician*** CreateMusiciansCollection(Musician* MusiciansGroup, int size_instruments, int size_musicians,Status* status_instruments)
{
	int i,logic_size;
	Musician*** MusiciansCollection = (Musician***)malloc(sizeof(Musician**) * size_instruments);
	checkMemoryFail(MusiciansCollection);
	for (i = 0; i < size_instruments; i++)
	{
		MusiciansCollection[i] = CreateNewMusicianArr(MusiciansGroup, i, size_musicians,&logic_size);
		status_instruments[i].size = logic_size;//updates the status of the instrument with the id i
		status_instruments[i].num_of_availables = logic_size;
	}
	return  MusiciansCollection;
}


/*the function creates and returns a new array of pointers to the musicians 
that plays on instrument with the id insId*/
Musician** CreateNewMusicianArr(Musician* MusiciansGroup, int insId, int size_musicians,int* logic_size)
{
	int i, j = 0;
	Musician** MusicianArr = (Musician**)malloc(sizeof(Musician*) * size_musicians);
	checkMemoryFail(MusicianArr);
	for (i = 0; i < size_musicians; i++)
	{
		if (findIdInList(&(MusiciansGroup[i].instruments), insId,NULL))//checks if the current musician plays on the instrument with the given id
		{
			MusicianArr[j] = &(MusiciansGroup[i]);
			j++;
		}
	}
	if (j != 0)
	{
		MusicianArr = (Musician**)realloc(MusicianArr, sizeof(Musician*) * j);
		checkMemoryFail(MusicianArr);	
	}
	else
	{ 
		free(MusicianArr);
		MusicianArr = NULL;
	}
	*logic_size = j;
	return MusicianArr;
}



/*This function returns true if an id was found on the list or false otherwise,in 
addition the function returns the node by refernce corresponding to the found id*/
bool findIdInList(MPIList* insList, int insId, LNODE** Node)
{
	LNODE* curr = insList->head;
	bool found = false;
	while (curr != NULL && !found)
	{
		if ((curr->data).insId == insId)
		{
			if (Node != NULL)
				*Node = curr;
			found = true;
		}
		curr = curr->next;
	}
	return found;
}


/*This function frees the allocated memory of the Musicians collection*/
void freeMusiciansCollection(Musician*** MusiciansCollection, int size_instruments)
{
	int i;
	for (i = 0; i < size_instruments; i++)
	{
		free(MusiciansCollection[i]);
	}
	free(MusiciansCollection);
}


/*This function frees the allocated memory of the musicians group*/
void freeMusicianGroup(Musician* arr, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		freeList(&(arr[i].instruments));
		freeArr(arr[i].name);
	}
	free(arr);
}


/*This function gets the concerts details from the user*/
char** getConcertsInput(int* size)
{
	char** arr;
	bool end = false;
	int physize = 1, logsize = 0;
	arr = (char**)malloc(sizeof(char*));
	checkMemoryFail(arr);

	while (end == false)
	{
		if (logsize >= physize)
		{
			arr = (char**)realloc(arr, sizeof(char*) * (physize * 2));
			checkMemoryFail(arr);
			physize *= 2;
		}


		arr[logsize] = readLine();//read single line (details of one concert)

		if (arr[logsize][0] == '\0')
		{
			end = true;
		}

		logsize++;
	}

	arr = (char**)realloc(arr, sizeof(char*) * (logsize));
	checkMemoryFail(arr);
	free(arr[logsize - 1]);
	arr[logsize - 1] = NULL;
	*size = logsize - 1;
	return arr;
}


/*This function reads a single line of input from the user(until \n is entered)*/
char* readLine()
{
	int physize = 1;
	int logsize = 1;
	char* arr = (char*)malloc(sizeof(char));
	checkMemoryFail(arr);

	scanf("%c", &arr[0]);
	while (arr[logsize - 1] != '\n')
	{
		if (logsize >= physize)
		{
			arr = (char*)realloc(arr, sizeof(char) * (physize * 2));
			checkMemoryFail(arr);
			physize *= 2;
		}
		scanf("%c", &arr[logsize]);
		logsize++;
	}

	arr = (char*)realloc(arr, sizeof(char) * logsize);
	checkMemoryFail(arr);
	arr[logsize - 1] = '\0';
	return arr;
}


/*the functions sorts all the  pointers to arrays of the given MusiciansCollection array*/
void SortMusicianCollection(Musician*** MusiciansCollection, Concert* concert, int size_instruments,Status* status_instruments)
{
	int i;
	ConcertInstrument instrument;
	bool exist;
	for (i = 0; i < size_instruments; i++)
	{
		exist = findInstrument(&(concert->instruments), i, &instrument);//checks if the instrument was requsted in the given concert
		if (MusiciansCollection[i] != NULL && exist)
		{
			SortMusicianArr(MusiciansCollection[i], status_instruments[i].size, instrument.importance, i);
		}
	}
}


/*
the function checks if the given id's instrument appears in given list of instruments 
if the given id's instrument found the functions returns the data of the found node.
*/
bool findInstrument(CIList* inslist, int insId, ConcertInstrument* instrument)
{
	CNODE* curr = inslist->head;
	bool found = false;
	while (curr != NULL && !found)
	{
		if (curr->data.inst == insId)
		{
			*instrument = curr->data;
			found = true;
		}
		curr = curr->next;
	}
	return found;
}



/*the function sorts the given musician arr of pointers by the given importance from the user
with the qsort build-in function*/
void  SortMusicianArr(Musician** MusicianArr, int size, char importance, int insId)
{
	adjustMusicianArr(MusicianArr, size, insId);
	switch (importance)
	{
	case IMPORTANT:
		qsort(MusicianArr, size, sizeof(Musician*), cmp_Important);
		break;
	case NOT_IMPORTANT:
		qsort(MusicianArr, size, sizeof(Musician*), cmp_Not_Important);
		break;
	default:
		break;
	}
}


/*
the function swaps the node with the needed instrument by the given id to the head of the list 
of every musician in the given musician array.
*/
void adjustMusicianArr(Musician** MusicianArr, int size, int insId)
{
	int i;
	LNODE* head, * node;

	for (i = 0; i < size; i++)
	{
		head = MusicianArr[i]->instruments.head;
		node = head;
		findIdInList(&(MusicianArr[i]->instruments), insId,&node);
		swapInstruments(&(head->data),&(node->data));
	}
}



/*the function swaps the data of the two given instrument data*/
void swapInstruments(MusicianPriceInstrument* data1, MusicianPriceInstrument* data2)
{
	MusicianPriceInstrument temp = (*data1);
	(*data1) = (*data2);
	(*data2) = temp;
}



/*the function returns the size ratio between the price's insturment of the two given of the musicians
with etmphasis on the higher quality between the two*/
int cmp_Important(void* var1, void* var2)
{

	Musician* musician1 = *(Musician**)var1;
	Musician* musician2 = *(Musician**)var2;

	return musician2->instruments.head->data.price - musician1->instruments.head->data.price;
}


/*the function returns the size ratio between the price's insturment of the two given of the musicians
with etmphasis on the lower quality between the two*/
int cmp_Not_Important(void* var1, void* var2)
{

	Musician* musician1 = *(Musician**)var1;
	Musician* musician2 = *(Musician**)var2;

	return musician1->instruments.head->data.price - musician2->instruments.head->data.price;
}


/*This function updates the concerts info(user input) into the needed formatand returns the concerts*/
Concert* formatConcerts(char** inputconcerts, int size, InstrumentTree* tr)
{
	int i;
	Concert* Concerts = (Concert*)malloc(sizeof(Concert) * size);
	checkMemoryFail(Concerts);

	for (i = 0; i < size; i++)
	{
		Concerts[i] = getConcertDetails(inputconcerts[i], tr);//Update the info of a single concert
	}

	return Concerts;
}


/*This function updates all the info of a single concert*/
Concert getConcertDetails(char* str, InstrumentTree* tr)
{
	Concert newConcert;
	makeEmptyCList(&(newConcert.instruments));
	char seps[] = " ";
	char* token;
	int index = 1;

	token = strtok(str, seps);//get first token (info)

	while (token != NULL)
	{
		concertDetailsSwitch(&newConcert, seps, &index, &token, tr);//updates current info and gets the next one
	}
	return newConcert;
}


/*This function updates the relevant info of the concert(index indicating what info to update)*/
void concertDetailsSwitch(Concert* newConcert, char* seps, int* index, char** token, InstrumentTree* tr)
{

	switch (*index)
	{
	case 1:
		GetConcertName(token, seps, newConcert, index);
		break;
	case 2:
		GetConcertDate(token, seps, newConcert, index);
		break;
	case 3:
		GetConcertHour(token, seps, newConcert, index);
		break;
	case 4:
		GetConcertInstrument(token, seps, newConcert, tr);
	}

}


/*This function updates the concerts name*/
void GetConcertName(char** token, char* seps, Concert* newConcert, int* index)
{

	newConcert->name = strdup(*token);
	checkMemoryFail(newConcert->name);
	*token = strtok(NULL, seps);
	(*index)++;
}


/*This function updates the concerts date(day, month, year)*/
void GetConcertDate(char** token, char* seps, Concert* newConcert, int* index)
{
	sscanf(*token, "%d", &(newConcert->date_of_concert.day));
	*token = strtok(NULL, seps);
	sscanf(*token, "%d", &(newConcert->date_of_concert.month));
	*token = strtok(NULL, seps);
	sscanf(*token, "%d", &(newConcert->date_of_concert.year));
	*token = strtok(NULL, seps);
	(*index)++;
}


/*This function updates the time of the concert in the format HH : MM*/
void GetConcertHour(char** token, char* seps, Concert* newConcert, int* index)
{
	int hours, minutes;
	sscanf(*token, "%d:%d", &hours, &minutes);
	(newConcert->date_of_concert.hour) = (float)hours + (minutes) / MINUTES_IN_HOUR;
	*token = strtok(NULL, seps);
	(*index)++;
}


/*This function adds the needed instrument for the concert to a list*/
void GetConcertInstrument(char** token, char* seps, Concert* newConcert, InstrumentTree* tr)
{
	ConcertInstrument newInstrument;

	newInstrument.inst = findInsId(tr, *token);
	char* numOfInstrument = strtok(NULL, seps);
	char* InstrumentImportance = strtok(NULL, seps);
	newInstrument.importance = InstrumentImportance[0];
	sscanf(numOfInstrument, "%d", &(newInstrument.num));

	insertDataToEndCList(&(newConcert->instruments), newInstrument);

	*token = strtok(NULL, seps);
}


/*This function frees the allocated memory of the concerts*/
void freeConcerts(Concert* Concerts, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		free(Concerts[i].name);
		freeCList(&(Concerts[i].instruments));
		free(Concerts[i].musicians_info);
	}
	free(Concerts);
}


//the function gets a file and returns the current line from the given file
char* GetLineFile(FILE* file)
{
	char tmp[LINE_SIZE];
	char* line;
	int size;

	line = fgets(tmp, LINE_SIZE, file);//returns the line where the cursor was in the begining of the function 
	if (line)
	{
		size = strlen(tmp);
		if (tmp[size - 1] == '\n')
		{
			tmp[size - 1] = '\0';
		}

		line = strdup(tmp);
		checkMemoryFail(line);
	}
	return line;
}



/*
the function checks for every concert from the given concerts array
if there is enough available musicians in the  given MusicianCollection array according to the requirements for the current concert
and then accordingly prints the needed information about the current concert.
*/
void ManageConcerts(Musician*** MusicianCollection, Concert* concerts, int num_of_concerts, Status* status_instruments, Musician* MusiciansGroup, int num_of_musicians, int num_of_instruments)
{
	int i, insId, size_info, logic_size = 0;
	CNODE* currinstrument;
	bool concert_go = true;

	for (i = 0; i < num_of_concerts; i++)
	{
		//sorts the entire MusicianCollection array with requirements of the current concert
		SortMusicianCollection(MusicianCollection, &(concerts[i]), num_of_instruments, status_instruments);
		size_info = getSizeMusicians(&(concerts[i]));//gets the number of all the requsted musicians for the current concert
		concerts[i].musicians_info = (Musician_Info*)malloc(sizeof(Musician_Info) * size_info);
		checkMemoryFail(concerts[i].musicians_info);

		currinstrument = concerts[i].instruments.head;
		while (currinstrument != NULL && concert_go)
		{

			insId = currinstrument->data.inst;//the id of the current instrument
			if (insId != -1)
			{
				//updates the number of available musicians in the status of instruments array
				UpdateAvailables(MusicianCollection[insId], &(status_instruments[insId]));
				if (status_instruments[insId].num_of_availables >= currinstrument->data.num)//if there is enough available musicians
				{
					//finds the needed musicians for the current concert
					FindMusiciansForInstrument(&(concerts[i]), MusicianCollection[insId], &logic_size, currinstrument->data, &(status_instruments[insId]));
				}
				else
					concert_go = false;
			}
			else
				concert_go = false;

			currinstrument = currinstrument->next;
		}
		printStatusConcert(&concert_go, &(concerts[i]), size_info);
		logic_size = 0;
		ResetAvailables(MusiciansGroup, num_of_musicians); //making all the musicians available for the next concert
	}
}


//the function prints the correct info about the concert accordingly to the status of the concert
void printStatusConcert(bool* concert_status, Concert* concert,int musicians_size)
{
	if (*concert_status)//the concert is going to take place
	{
		printConcert(concert, musicians_size); //prints the info about the concert
	}
	else
	{
		printf("Could not find musicians for the concert %s\n", concert->name);
		free(concert->musicians_info);
		concert->musicians_info = NULL;
		*concert_status = true;
	}
}


/*the function updates the status of available musicians in the given musician array*/
void UpdateAvailables(Musician** MusicianArr, Status* status_instrument)
{
	int i, counter = 0;
	for (i = 0; i < status_instrument->size; i++)
	{
		if (MusicianArr[i]->available)
			counter++;

	}
	status_instrument->num_of_availables = counter;
}


/*the function makes all the musicians avaliable.*/
void ResetAvailables(Musician* MusiciansGroup, int num_of_musicians)
{
	int i = 0;
	for (i = 0; i < num_of_musicians; i++)
	{
		MusiciansGroup[i].available = true;
	}
}


/*
the function finds the first (data.num) avaliable musicians in the given musician array
and for every avaliable musician the function stores all the info of the current musician 
in the given concert and then changes the musician to be unavaliable.
*/
void FindMusiciansForInstrument(Concert* concert, Musician** MusicianArr, int* logic_size, ConcertInstrument data, Status* status_instrument)
{
	int i, counter = 0;
	LNODE* node;
	for (i = 0; i < status_instrument->size && counter < data.num; i++)
	{
		if (MusicianArr[i]->available)
		{
			node = MusicianArr[i]->instruments.head;
			concert->musicians_info[*logic_size].name_musician = MusicianArr[i]->name;
			findIdInList(&(MusicianArr[i]->instruments), data.inst,&node);
			concert->musicians_info[*logic_size].price = node->data.price;
			concert->musicians_info[*logic_size].name_instrument = node->data.name;
			MusicianArr[i]->available = false;
			(*logic_size)++;
			(*status_instrument).num_of_availables--;
			counter++;
		}
	}


}


/*the function calculates and then returns the number of requsted musicians for the given concert*/
int getSizeMusicians(Concert* concert)
{
	CNODE* curr = concert->instruments.head;
	int count = 0;

	while (curr != NULL)
	{
		count += curr->data.num;
		curr = curr->next;
	}
	return count;
}



/*This function prints the info of a single concert*/
void printConcert(Concert* concert, int musicians_size)
{
	int i, concert_price = 0, minutes;

	minutes = (concert->date_of_concert.hour - ((int)concert->date_of_concert.hour) * 1.0) * (int)MINUTES_IN_HOUR;// calculates the minutes for the time of the concert

	printf("%s ", concert->name);
	printf("%02d %02d %04d ", concert->date_of_concert.day, concert->date_of_concert.month, concert->date_of_concert.year);
	printf("%02d:%02d: ", (int)concert->date_of_concert.hour, minutes);

	for (i = 0; i < musicians_size; i++)
	{
		printName(concert->musicians_info[i].name_musician);
		printf("%s (%d)", concert->musicians_info[i].name_instrument, (int)concert->musicians_info[i].price);
		if (i == musicians_size - 1) {
			printf(". ");
		}
		else {
			printf(", ");
		}
		concert_price += (int)concert->musicians_info[i].price;
	}
	printf("Total cost: %d.\n", concert_price);
}


/*This function prints the full name of a single musician*/
void printName(char** name)
{
	int i = 0;

	while (name[i] != NULL)
	{
		printf("%s ", name[i]);
		i++;
	}
	printf("- ");
}