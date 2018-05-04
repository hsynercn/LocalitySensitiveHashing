#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputUtil.h"
#include "PoorMansHashTable.h"
#include "ShingleUtil.h"

void minHashTableFromShingleSet(struct MY_HASH_MAP *shingleSetA, struct MY_HASH_MAP *shingleSetB)
{
    long int filledA = countFilledSlots(shingleSetA);
    long int filledB = countFilledSlots(shingleSetB);
    long int common = commonShingleCount(shingleSetB, shingleSetA);
    int neededSize = filledA + filledB - common;
    
    int *vectorA = (int*)malloc(neededSize * sizeof(char));
    int *vectorB = (int*)malloc(neededSize * sizeof(char));
    
    char **unifiedSet = (char**)malloc(neededSize * sizeof(char*));
    
    if(unifiedSet == NULL)
    {
        printf("Memory allocation problem.");
        return;
    }
    
    for(int i=0;i<neededSize;i++)
    {
        unifiedSet[i] = (char*)malloc(SHINGLE_MAX_STR_LEN * sizeof(char*));
        unifiedSet[i][0] = EMPTY_CHAR;
        unifiedSet[i][1] = EMPTY_CHAR;
        unifiedSet[i][2] = EMPTY_CHAR;
        unifiedSet[i][3] = EMPTY_CHAR;
        unifiedSet[i][4] = EMPTY_CHAR;
        unifiedSet[i][5] = EMPTY_CHAR;
        unifiedSet[i][6] = EMPTY_CHAR;
        unifiedSet[i][7] = EMPTY_CHAR;
        unifiedSet[i][SHINGLE_MAX_STR_LEN-1] = '\0';
        printf("%d>%s\n",i,unifiedSet[i]);
        vectorA[i]=0;
        vectorB[i]=0;
    }
    
    if(unifiedSet == NULL)
    {
        printf("Allocated memory fail!");
        return;
    }
    
    for(int i=0;i<neededSize;i++)
    {
        //char *test3 = unifiedSet[i];
        printf("%d>>>%s\n",i,unifiedSet[i]);
    }
    
    int counter=0;
    
    for(int i=0;i<SHINGLE_SET_MAP_SIZE;i++)
    {
        if(shingleSetA->keys[i]!=EMPTY_KEY)
        {
            char *test1 = shingleSetA->values[i];
            char *test2 = unifiedSet[counter];
            
            int strSize =  strLen(shingleSetA->values[i]);
            
            strncpy(unifiedSet[counter], shingleSetA->values[i], strSize);
            unifiedSet[counter][strSize] = '\0';
            
            vectorA[i] = 1;
            if(searchValueSlot(unifiedSet[counter],shingleSetB)>0)
            {
                vectorB[i] = 1;
            }
            counter++;
        }
    }
    
    for(int i=0;i<SHINGLE_SET_MAP_SIZE;i++)
    {
        if(shingleSetB->keys[i]!=EMPTY_KEY)
        {
            if(searchValueSlot(shingleSetB->values[i],shingleSetA)<=0)
            {
                int strSize =  strLen(shingleSetB->values[i]);
                strncpy(unifiedSet[counter], shingleSetA->values[i], strSize);
                unifiedSet[counter][strSize] = '\0';
                vectorB[i] = 1;
                counter++;
            }
        }
    }
    
    printf("filledCounter:%d\n",counter);
    for(int i=0;i<neededSize;i++)
    {
        printf("i:%d key>%s A:%d B:%d\n",i , unifiedSet[i], vectorA[i], vectorB[i]);
    }
    
}

int main(int argc, char **argv)
{
    struct MY_HASH_MAP *shingleSetA = generateKShingleSetOfFile("D:/C-C++/Git/LocalitySensitiveHashing/SampleA.txt", 4);
    dumpHashMap(shingleSetA);
    
    struct MY_HASH_MAP *shingleSetB = generateKShingleSetOfFile("D:/C-C++/Git/LocalitySensitiveHashing/SampleB.txt", 4);
    dumpHashMap(shingleSetB);
    
    /*long int filledA = countFilledSlots(shingleSetA);
    long int filledB = countFilledSlots(shingleSetB);
    long int common = commonShingleCount(shingleSetB, shingleSetA);
    float jaccard = jaccardSimilarity(shingleSetB, shingleSetA);*/
    
    minHashTableFromShingleSet(shingleSetA, shingleSetB);
    
    return 0;
}
