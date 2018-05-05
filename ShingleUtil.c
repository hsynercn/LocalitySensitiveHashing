#include "ShingleUtil.h"
#include "PoorMansHashTable.h"
#include <stdlib.h>
#include <limits.h>

int *initializeEmptySignature(int singatureLen)
{
    int *signatureA = malloc(singatureLen * sizeof(int));
    for(int i=0;i<singatureLen;i++)
    {
        signatureA[i] = INT_MAX;
    }
    return signatureA;
}

int *initilizeSignatureHashConstants(int singatureLen, int valueLimit)
{
    int *hashFunctionConstants = malloc(singatureLen * sizeof(int));
    if(hashFunctionConstants == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }
    for(int i=0;i<singatureLen;i++)
    {
        hashFunctionConstants[i] = rand()%valueLimit;
    }
    return hashFunctionConstants;
}

struct MY_HASH_MAP *generateKShingleSet(long int stringLen, char* string, int k)
{
    struct MY_HASH_MAP *shingleSet = newMyHashMap();
    char *kWindow = (char*)malloc((k+1) * sizeof(char));
    for(int i=0;i<(stringLen-k);i++)
    {
        for(int j=0;j<k;j++)
        {
            kWindow[j] = string[i+j];
        }
        kWindow[k] = '\0';
        insert(kWindow, shingleSet);
    }
    free(kWindow);
    return shingleSet;
}

struct MY_HASH_MAP *generateKShingleSetOfFile(char *fileName, int k)
{
    long int outputTextSize = 0;
    char temp = 't';
    char *outputBuffer = &temp;
    char **outputBufferPointer = &outputBuffer;
    
    readInputFile(fileName, &outputTextSize, outputBufferPointer);

    if(outputTextSize == -1)
    {
        printf("Program execution halted due to invalid input string.");
    }
    
    long int filteredTextSize = 0;
    char temp2 = 't';
    char *filteredBuffer = &temp2;
    char **filteredBufferPointer = &filteredBuffer;
    
    formatInputText(outputTextSize, outputBuffer, &filteredTextSize, filteredBufferPointer);
    struct MY_HASH_MAP *shingleSet = generateKShingleSet(filteredTextSize, filteredBuffer, k);
    
    free(outputBuffer);
    free(filteredBuffer);
    //dumpHashMap(shingleSet);
    return shingleSet;
}

long int commonShingleCount( struct MY_HASH_MAP *shingleSetA,  struct MY_HASH_MAP *shingleSetB)
{
    long int commonShingleCount = 0; 
    for(int i=0;i<shingleSetA->hashMapSize;i++)
    {
        if(shingleSetA->keys[i] != EMPTY_KEY)
        {
            int long slotNum = searchValueSlot(shingleSetA->values[i], shingleSetB);
            if(slotNum>0)
            {
                commonShingleCount++;
            }
        }
    }
    return commonShingleCount;
}

float jaccardSimilarity(struct MY_HASH_MAP *shingleSetA,  struct MY_HASH_MAP *shingleSetB)
{
    long int filledA = countFilledSlots(shingleSetA);
    long int filledB = countFilledSlots(shingleSetB);
    long int common = commonShingleCount(shingleSetB, shingleSetA);
    return (float)common/(float)(filledA + filledB - common);
}

int getUnifiedSetCount(struct MY_HASH_MAP *shingleSetA, struct MY_HASH_MAP *shingleSetB)
{
    long int filledA = countFilledSlots(shingleSetA);
    long int filledB = countFilledSlots(shingleSetB);
    long int common = commonShingleCount(shingleSetB, shingleSetA);
    return filledA + filledB - common;
}