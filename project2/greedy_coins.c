#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef struct {
    int numCoins;
	int size;
    int* allocation;
    int* denominations;
} changeBack;

struct timeval time_start, time_stop, run_time, t;



/* ***************************************************************
 *					  FUNCTION DECLARATIONS						 *
 *************************************************************** */


changeBack greedy_Coins(int* denominations, int value);
int* parseArray(char* line);
void getLine(FILE* inFile, FILE* outFile);
FILE* openFile(const char* filname);
void timeRightNow(FILE* outFile);
void printChange(changeBack change);
int arraySize;



/* ***************************************************************
 *						  MAIN FUNCTION							 *
 *************************************************************** */


int main(){
    
    const char* fileIn = "coins1.txt";
    const char* fileOut = "Coins_Results.txt";
    FILE *fpIn, *fpOut;
    
    fpIn = openFile(fileIn);
    fpOut = openFile(fileOut);
    
    getLine(fpIn, fpOut);
    
    fclose(fpIn);
    fclose(fpOut);
	   
    return 0;
}



/* ***************************************************************
 *						SUPPLEMENTAL FUNCTION					 *
 *************************************************************** */


changeBack greedy_Coins(int* denominations, int value){
    
    int i, temp;
	
	changeBack change;
	change.numCoins = 0;
	change.size = arraySize;
	change.denominations = denominations;
    change.allocation = malloc(sizeof(arraySize));
    
    for(i = (arraySize-1); i > -1; i--){
        
        temp = value / denominations[i];
        change.allocation[i] = temp;
        change.numCoins = change.numCoins + temp;
        value = value - (temp * denominations[i]);
    }
    
	return change;
}


int* parseArray(char* passedLine){
    
    char* token;
    char line[256];
    int nextNum, i = 0;
    int* parsedArray = malloc(256);
    
    memset(&line, 0, sizeof(line));
    memcpy(&line, passedLine, 256);
    line[0] = ' ';
    token = strtok(line, ",");
    
    while(token != NULL){
        sscanf(token, "%d", &nextNum);
        parsedArray[i] = nextNum;
        i++;
        token = strtok(NULL,",");
    }
    arraySize = i;
    return parsedArray;
}


void getLine(FILE* inFile, FILE* outFile){
    
    char lineIn[256];
	char buffer[256];
    int* parsedArray;
    int value;
    changeBack change;
    while ( fgets(lineIn, sizeof(lineIn), inFile) != NULL ){
        
        printf("\n\n\n*********** GREEDY CHANGE ***********");
        //fprintf(outFile, "\n*********** ALGORITHM 4 ***********\n");
        parsedArray = parseArray(lineIn);
        fgets(buffer, sizeof(lineIn), inFile);
        value = atoi(buffer);
        gettimeofday(&time_start, NULL);
        change = greedy_Coins(parsedArray, value);
        gettimeofday(&time_stop, NULL);
        printChange(change);
        timeRightNow(outFile);
    }
    free(parsedArray);
}


FILE* openFile(const char* filename){
    
    FILE *file = fopen(filename, "a+");
    
    if(file != NULL){
        return file;
    }
    else{
        printf("\nFailed to open %s", filename);
    }	
}


void printChange(changeBack change){
    int i;
    
	printf("\nNumber of coins per denomination:");
	for(i = 0; i < change.size; i++){
		printf("\nDenomination: %d \t\tInstances: %d", change.denominations[i], change.allocation[i]);
	}
	printf("\n\nTotal Coins: %d", change.numCoins);
}


void timeRightNow(FILE* outFile){
    
    timersub(&time_stop, &time_start, &run_time);
    printf("\nComputed in %ld.%06ld\n", (long int)run_time.tv_sec, (long int)run_time.tv_usec);
    fprintf(outFile, "\nComputed in %ld.%06ld\n", (long int)run_time.tv_sec, (long int)run_time.tv_usec);
}

