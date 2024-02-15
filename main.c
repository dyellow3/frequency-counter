#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "mergeSort.h"

/*
The token structure, that is included in mergeSort.h
Tokens will represent each word in the input file

struct token {
    char val[50]; // Max length of 50
    int count; 
    int occupied;
};
*/

// Naive solution, bad
void naiveSolution(struct token tokens[], FILE *fptr, char buffer[], int size, int *c) {
    // linear scan through each word in the file
    while(fscanf(fptr, "%49s", buffer)==1) {
        int index = 0;
        bool flag = false;
        // search through our current tokens and compare with current word in buffer
        for(int i = 0; i < size; i++) {
            if(strcmp(buffer, tokens[i].val)==0) {
                flag = true;
                index = i;
                // stop the for loop if we find it
                break;
            }
        }
        
        // if the word was in the array, increase count
        if(flag) {
            tokens[index].count++;
        }
        // else we add it to our tokens array
        else {
            tokens[size].count = 1;
            strcpy(tokens[size].val,buffer);
            size++;          
        }
        (*c)++;                
    }
}


// Hash solution, good
// the hash function - returns a valid index given the word
uint32_t hashFunction(char buffer[50], int i, int arraySize) {
    uint32_t result = 0;
    // exit if the buffer given is empty
    // or if the array is of size 0
    int len = strlen(buffer);
    if (len == 0 || arraySize == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        exit(EXIT_FAILURE);
    }

    // for each character in the buffer , we add it to result
    for(int j = 0; j < len; j++) {
        result = (result+i)*33 + (uint32_t)buffer[j];
    }

    // mod the result by the size of the array, ensures we stay in range
    return (result)%arraySize;
}
void hashSolution(struct token tokens[], FILE *fptr, char buffer[], int size, int *c, int *collisionCount) {
    // scan through each word in the file, store it in buffer
    while(fscanf(fptr, "%49s", buffer)==1) {
        // i will be used in the case of collision, in which we will linear probe
        // that is, keep iterating till we find an open slot in the array 
        int i = 0;
        uint32_t result = hashFunction(buffer, i, size);

        // collision case 
        while(strcmp(tokens[result].val, buffer)!=0 && tokens[result].occupied == 1) {
            // increment i, linear probe to find new available slot
            i++;
            (*collisionCount)++;
            // get a new result using our incremented i
            result = hashFunction(buffer, i, size);
        }

        // add the current word to our array if its not in already
        if(tokens[result].occupied == 0) {
            strcpy(tokens[result].val, buffer);
            tokens[result].occupied = 1;
            tokens[result].count++;
        }
        // else increment the count
        else {
            tokens[result].count++;
        }
        (*c)++;
    }
}


int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("File input not detected. Program will now exit\n");
        exit(0);
    }
    
    FILE *fptr;
    fptr = fopen(argv[1], "r");
    if(fptr == NULL) {
        printf("The file is not opended. The program will now exit");
        exit(0);
    }

    int limit = -1;
    printf("Enter how many of the most frequent words to print (enter nothing for default of 10)\n");
    scanf("%d", &limit);

    if(limit == -1) { limit = 10; }  
    
    // buffer will hold the current token (word)
    char buffer[50];
    // array to hold all the tokens (token value, token count, token occupied status)
    // need to consider a way to set the size of array dynamically
    struct token tokens[69000] = {{"", 0, 0}};
    int tokenCount = 0;
    int collisionCount = 0;

    clock_t start, stop;
    double duration;

    int userSelection = 2;
    printf("Select: (1) Naive Solution Only , (2 - Default) Hash Solution Only , (3) Both Solutions\n");
    scanf("%d", &userSelection);
    if(userSelection > 3 || userSelection < 0) { userSelection = 2; }

    if(userSelection == 3) {
        start = clock();
        naiveSolution(tokens, fptr, buffer, 0, &tokenCount); 
        stop = clock();
        duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
        printf("Time taken by Naive Solution: %f seconds\n", duration);

        // Reset the tokens array
        memset(tokens, 0, sizeof(tokens));
        tokenCount = 0;
        rewind(fptr);

        start = clock();
        hashSolution(tokens, fptr, buffer, 69000, &tokenCount, &collisionCount);
        stop = clock(); 
        duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
        printf("Time taken by Hash Solution: %f seconds\n", duration);
        printf("%d Collisions\n", collisionCount);
    }
    else if(userSelection == 2) {
        start = clock();
        hashSolution(tokens, fptr, buffer, 69000, &tokenCount, &collisionCount);
        stop = clock(); 
        duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
        printf("Time taken by Hash Solution: %f seconds\n", duration);
        printf("%d Collisions\n", collisionCount);
    }
    else {
        start = clock();
        naiveSolution(tokens, fptr, buffer, 0, &tokenCount); 
        stop = clock();
        duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
        printf("Time taken by Naive Solution: %f seconds\n", duration);
    }

    printf("\n%i tokens\n", tokenCount);
    
    // if the limit the user gave is more than the token count, we must do something
    if(limit > tokenCount) { limit = tokenCount; }

    // sort the tokens array so we can easily print the most frequent tokens
    mergeSort(tokens, 0, 68999);
    for(int i = 0; i < limit; i++) {
       printf("   %d, %s\n", tokens[i].count, tokens[i].val);
    }

    fclose(fptr);
    return 0;
}
