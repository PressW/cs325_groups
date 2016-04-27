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
void printChange(changeBack change, FILE* outFile);
void largeArray(FILE* outFile);
void csvPrint(changeBack largeChange, int A, FILE* outFile);
int arraySize;



/* ***************************************************************
 *						  MAIN FUNCTION							 *
 *************************************************************** */


int main(){
    
    const char* fileIn = "coins1.txt";
    const char* fileOut = "Coins_Results.csv";
    FILE *fpIn, *fpOut;
    
    fpIn = openFile(fileIn);
    fpOut = openFile(fileOut);
    
    //getLine(fpIn, fpOut);
	largeArray(fpOut);
    
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


void largeArray(FILE* outFile){
	
	int i;
	int v1[5] = {1, 5, 10, 25, 50};
	int v2[7] = {1, 2, 6, 12, 24, 48, 60};
	int v3[5] = {1, 6, 13, 37, 150};
	int v4[16] = {1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
	changeBack largeChange;
	
	fprintf(outFile, "\n\n\n*********** ARRAY V1 ***********");
	for(i = 2010; i < 2201; i=i+5){
		
		arraySize = 5;
		//printf("\n\n\n*********** GREEDY CHANGE ***********");
		//fprintf(outFile, "\n\n\n*********** GREEDY CHANGE ***********");
		printf("\nValue for A: %d", i);
		gettimeofday(&time_start, NULL);
		largeChange = greedy_Coins(v1, i);
		gettimeofday(&time_stop, NULL);
		//printChange(largeChange, outFile);
		csvPrint(largeChange, i, outFile);
        //timeRightNow(outFile);
	}
	
	fprintf(outFile, "\n\n\n*********** ARRAY V2 ***********");
	for(i = 2000; i < 2201; i++){
		
		arraySize = 7;
		//printf("\n\n\n*********** GREEDY CHANGE ***********");
		//fprintf(outFile, "\n\n\n*********** GREEDY CHANGE ***********");
		printf("\nValue for A: %d", i);
		gettimeofday(&time_start, NULL);
		largeChange = greedy_Coins(v2, i);
		gettimeofday(&time_stop, NULL);
		//printChange(largeChange, outFile);
		csvPrint(largeChange, i, outFile);
        //timeRightNow(outFile);
	}
	
	fprintf(outFile, "\n\n\n*********** ARRAY V3 ***********");
	for(i = 10000; i < 10101; i++){
		
		arraySize = 5;
		//printf("\n\n\n*********** GREEDY CHANGE ***********");
		//fprintf(outFile, "\n\n\n*********** GREEDY CHANGE ***********");
		printf("\nValue for A: %d", i);
		gettimeofday(&time_start, NULL);
		largeChange = greedy_Coins(v3, i);
		gettimeofday(&time_stop, NULL);
		//printChange(largeChange, outFile);
		csvPrint(largeChange, i, outFile);
        //timeRightNow(outFile);
	}
	
	fprintf(outFile, "\n\n\n*********** ARRAY V4 ***********");
	for(i = 2000; i < 2201; i++){
		
		arraySize = 16;
		//printf("\n\n\n*********** GREEDY CHANGE ***********");
		//fprintf(outFile, "\n\n\n*********** GREEDY CHANGE ***********");
		printf("\nValue for A: %d", i);
		gettimeofday(&time_start, NULL);
		largeChange = greedy_Coins(v4, i);
		gettimeofday(&time_stop, NULL);
		//printChange(largeChange, outFile);
		csvPrint(largeChange, i, outFile);
        //timeRightNow(outFile);
	}
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
		fprintf(outFile, "\n\n\n*********** GREEDY CHANGE ***********");
        parsedArray = parseArray(lineIn);
        fgets(buffer, sizeof(lineIn), inFile);
        value = atoi(buffer);
        gettimeofday(&time_start, NULL);
        change = greedy_Coins(parsedArray, value);
        gettimeofday(&time_stop, NULL);
        printChange(change, outFile);
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


void printChange(changeBack change, FILE* outFile){
    int i;
    
	printf("\nNumber of coins per denomination:");
	fprintf(outFile, "\nNumber of coins per denomination:");
	for(i = 0; i < change.size; i++){
		printf("\nDenomination: %d \t\tInstances: %d", change.denominations[i], change.allocation[i]);
		fprintf(outFile, "\nDenomination: %d \t\tInstances: %d", change.denominations[i], change.allocation[i]);
	}
	printf("\n\nTotal Coins: %d", change.numCoins);
	fprintf(outFile, "\n\nTotal Coins: %d", change.numCoins);
}


void csvPrint(changeBack change, int A, FILE* outFile){
	timersub(&time_stop, &time_start, &run_time);
	fprintf(outFile, "\n%d,%d,%ld.%09ld", A, change.numCoins, (long int)run_time.tv_sec, (long int)run_time.tv_usec);
	printf("\n%d,%d", A, change.numCoins);
	printf("\nComputed in %ld.%09ld\n", (long int)run_time.tv_sec, (long int)run_time.tv_usec);
}


void timeRightNow(FILE* outFile){
    
    timersub(&time_stop, &time_start, &run_time);
    printf("\nComputed in %ld.%09ld\n", (long int)run_time.tv_sec, (long int)run_time.tv_usec);
    fprintf(outFile, "\nComputed in %ld.%09ld\n", (long int)run_time.tv_sec, (long int)run_time.tv_usec);
}

