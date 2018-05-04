#include "ShingleUtil.h"
#include "PoorMansHashTable.h"

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