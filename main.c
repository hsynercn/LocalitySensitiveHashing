#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputUtil.h"
#include "PoorMansHashTable.h"
#include "ShingleUtil.h"

void minHashTableFromShingleSet(struct MY_HASH_MAP *shingleSetA, struct MY_HASH_MAP *shingleSetB)
{
    int neededSize = getUnifiedSetCount(shingleSetA, shingleSetB);
    
    int *vectorA = malloc(neededSize * sizeof(int));
    int *vectorB = malloc(neededSize * sizeof(int));
    
    char **unifiedSet = malloc(neededSize * sizeof(char*));
    
    if(unifiedSet == NULL)
    {
        printf("Memory allocation problem.");
        return;
    }
    
    for(int i=0;i<neededSize;i++)
    {
        unifiedSet[i] = malloc(SHINGLE_MAX_STR_LEN * sizeof(char));
        if(unifiedSet[i]==NULL)
        {
            printf("Can't allocate memeroy!");
            exit(1);
        }
        for(int j=0;j<SHINGLE_MAX_STR_LEN-2;j++)
        {
            unifiedSet[i][j] = EMPTY_CHAR;
        }
        unifiedSet[i][SHINGLE_MAX_STR_LEN-1] = '\0';
        vectorA[i]=0;
        vectorB[i]=0;
    }

    int counter=0;
    
    for(int i=0;i<SHINGLE_SET_MAP_SIZE;i++)
    {
        if(shingleSetA->keys[i]!=EMPTY_KEY)
        {
            int strSize =  strLen(shingleSetA->values[i]);
            
            strncpy(unifiedSet[counter], shingleSetA->values[i], strSize);
            unifiedSet[counter][strSize] = '\0';
            
            vectorA[counter] = 1;
            if(searchValueSlot(unifiedSet[counter],shingleSetB)>0)
            {
                vectorB[counter] = 1;
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
                vectorB[counter] = 1;
                counter++;
            }
        }
    }
    
    printf("filledCounter:%d\n",counter);
    for(int i=0;i<neededSize;i++)
    {
        printf("set:%d key>%s< A:%d B:%d\n",i , unifiedSet[i], vectorA[i], vectorB[i]);
    }
    
    int unifiedSetCount = neededSize;
    
    int *hashFunctionConstants = initilizeSignatureHashConstants(SIGNATURE_LENGTH, unifiedSetCount);
    
    for(int i=0;i<SIGNATURE_LENGTH;i++)
    {
        printf("const %d : %d\n",i,hashFunctionConstants[i]);
    }
    
    int *signatureA = initializeEmptySignature(SIGNATURE_LENGTH);
    int *signatureB = initializeEmptySignature(SIGNATURE_LENGTH);
    
    for(int i=0;i<unifiedSetCount;i++)
    {
        printf("vectorA[ %d ]:%d   vectorA[ %d ]:%d\n ",i,vectorA[i],i,vectorB[i]);
        
        if(vectorA[i]!=0)
        {
            for(int signatureDigit=0;signatureDigit<SIGNATURE_LENGTH;signatureDigit++)
            {
                int selectedSetLocation = (hashFunctionConstants[signatureDigit]*(i+1) + 1)%unifiedSetCount;
                
                printf("signatureDigit:%d  SetLocation:%d\n",signatureDigit,selectedSetLocation);
                int temp = signatureA[signatureDigit];
                if(signatureA[signatureDigit]>selectedSetLocation)
                {
                    printf("sig:%d select:%d\n",signatureA[signatureDigit],selectedSetLocation);
                    signatureA[signatureDigit] = selectedSetLocation;
                }
            }
        }
        
        if(vectorB[i]!=0)
        {
            for(int signatureDigit=0;signatureDigit<SIGNATURE_LENGTH;signatureDigit++)
            {
                int selectedSetLocation = (hashFunctionConstants[signatureDigit]*(i+1) + 1)%unifiedSetCount;
                
                printf("signatureDigit:%d  SetLocation:%d\n",signatureDigit,selectedSetLocation);
                int temp = signatureA[signatureDigit];
                if(signatureB[signatureDigit]>selectedSetLocation)
                {
                    printf("sig:%d select:%d\n",signatureB[signatureDigit],selectedSetLocation);
                    signatureB[signatureDigit] = selectedSetLocation;
                }
            }
        }
    }
    int signatureSimilarity = 0;
    for(int i=0;i<SIGNATURE_LENGTH;i++)
    {
        if(signatureA[i]!=signatureB[i])
        {
            signatureSimilarity++;
        }
        printf("i: %d  sigA: %d  sigB: %d\n",i,signatureA[i],signatureB[i]);
    }
    printf("differance %d / %d",signatureSimilarity,SIGNATURE_LENGTH);
    
    return;
}

int main(int argc, char **argv)
{
    struct MY_HASH_MAP *shingleSetA = generateKShingleSetOfFile("D:/C-C++/Git/LocalitySensitiveHashing/SampleA.txt", 4);
    //dumpHashMap(shingleSetA);
    
    struct MY_HASH_MAP *shingleSetB = generateKShingleSetOfFile("D:/C-C++/Git/LocalitySensitiveHashing/SampleE.txt", 4);
    //dumpHashMap(shingleSetB);
    

    float jaccard = jaccardSimilarity(shingleSetB, shingleSetA);
    printf("Jaccard:%f\n", jaccard);
    
    minHashTableFromShingleSet(shingleSetA, shingleSetB);
    
    return 0;
}
