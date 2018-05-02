#include "PoorMansHashTable.h"
#include <stdio.h>
#include <stdlib.h>


struct MY_HASH_MAP *newMyHashMap()
{
    struct MY_HASH_MAP *myHashMap = malloc (sizeof (struct MY_HASH_MAP));
    myHashMap->hashMapSize = SHINGLE_SET_MAP_SIZE;
    char **values = malloc(myHashMap->hashMapSize * sizeof(char*));
    for(int i=0;i<myHashMap->hashMapSize;i++)
    {
        values[i] = malloc(SHINGLE_MAX_STR_LEN * sizeof(char));
        values[i][0] = EMPTY_CHAR;
        values[i][1] = EMPTY_CHAR;
        values[i][2] = EMPTY_CHAR;
        values[i][3] = EMPTY_CHAR;
        values[i][4] = EMPTY_CHAR;
        values[i][5] = EMPTY_CHAR;
        values[i][6] = EMPTY_CHAR;
        values[i][7] = EMPTY_CHAR;
        values[i][SHINGLE_MAX_STR_LEN-1] = '\0';

    }
    myHashMap->values = values;
    myHashMap->keys = malloc(myHashMap->hashMapSize * sizeof(int));
    for(int i=0;i<myHashMap->hashMapSize;i++)
    {
        myHashMap->keys[i] = EMPTY_KEY;
    }
    
    return myHashMap;
}

void dumpHashMap(struct MY_HASH_MAP *myHashMap)
{
    for(int i=0;i<myHashMap->hashMapSize;i++)
    {
        printf(">slt:%d k:%d v>%s<\n",i,myHashMap->keys[i],myHashMap->values[i]);
    }
}

long int countFilledSlots(struct MY_HASH_MAP *myHashMap)
{
    long int filled = 0;
    for(int i=0;i<myHashMap->hashMapSize;i++)
    {
        if(myHashMap->keys[i] != EMPTY_KEY)
        {
            filled++;
        }
    }
    return filled;
}

int strLen(char* string)
{
    if(string==NULL)
    {
        return 1;
    }
    int len = 0;
    while (string[len] != '\0')
    {
        len++;
    }
    return len;
}

long int stringToNum(char* string)
{
    int len = strLen(string);
    if(len<0)
    {
        return len; 
    }
    long int val = 0;
    for(int i=0;i<len;i++)
    {
        val = val*10 + string[i];
    }
    return val;
}

int getHashValue(char* string)
{
    return stringToNum(string)%SHINGLE_SET_MAP_SIZE;
}

int long insert(char* string, struct MY_HASH_MAP *myHashMap)
{
    int len = strLen(string);
    long int slotNum = getHashValue(string)%SHINGLE_SET_MAP_SIZE;
    if(myHashMap->keys[slotNum] == EMPTY_KEY)
    {
        //one shot one kill
        if(len>SHINGLE_MAX_STR_LEN)
        {
            printf("Can't insert the value, exceeds SHINGLE_MAX_STR_LEN.");
            return CANT_INSERT_LONG_STR;
        }
        myHashMap->keys[slotNum] = slotNum;
        strncpy(myHashMap->values[slotNum], string, len);
        myHashMap->values[slotNum][len] = '\0';
        return slotNum;
    }
    else
    {
        int isInserted = -1;
        long int slotIterator = slotNum;
        while(isInserted==-1 && slotIterator<SHINGLE_SET_MAP_SIZE)
        {
            if(myHashMap->keys[slotIterator%SHINGLE_SET_MAP_SIZE] == EMPTY_KEY)
            {
                
                if(len>SHINGLE_MAX_STR_LEN)
                {
                    printf("Can't insert the value, exceeds SHINGLE_MAX_STR_LEN.");
                    return CANT_INSERT_LONG_STR;
                }
                myHashMap->keys[slotIterator%SHINGLE_SET_MAP_SIZE] = slotIterator%SHINGLE_SET_MAP_SIZE;
                strncpy(myHashMap->values[slotIterator%SHINGLE_SET_MAP_SIZE], string, len);
                myHashMap->values[slotIterator%SHINGLE_SET_MAP_SIZE][len] = '\0';
                isInserted = 1;
            }
            else
            {
                char *test = myHashMap->values[slotIterator%SHINGLE_SET_MAP_SIZE];
                //printf("DEBUG>%s\n",myHashMap->values[slotIterator%SHINGLE_SET_MAP_SIZE]);
                if(strcmp(string, myHashMap->values[slotIterator%SHINGLE_SET_MAP_SIZE])==0)
                {
                    return CANT_INSERT_VALUE_IN_SET;
                }
            }
            slotIterator++;
        }
        
        if(isInserted==1)
        {
            return (slotIterator--)%SHINGLE_SET_MAP_SIZE;
        }
        
        if(slotIterator>=SHINGLE_SET_MAP_SIZE)
        {
            return CANT_INSERT_MAP_FULL;
        }
        return CANT_INSERT_UNKOWN_ERROR;
    }
}

int long searchValueSlot(char* string, struct MY_HASH_MAP *myHashMap)
{
    int len = strLen(string);
    if(len>SHINGLE_MAX_STR_LEN)
    {
        printf("Can't insert the value, exceeds SHINGLE_MAX_STR_LEN.");
        return CANT_SEARCH_LONG_STR;
    }
    long int slotNum = getHashValue(string)%SHINGLE_SET_MAP_SIZE;
     
    if(myHashMap->keys[slotNum] == EMPTY_KEY)
    {
        return VALUE_IS_NOT_IN_MAP;
    }
    else
    {
        long int slotIterator = slotNum;
        while(slotIterator<SHINGLE_SET_MAP_SIZE)
        {
            if(myHashMap->keys[slotIterator%SHINGLE_SET_MAP_SIZE] == EMPTY_KEY)
            {
                return VALUE_IS_NOT_IN_MAP;
            }
            else
            {
                char *test = myHashMap->values[slotIterator%SHINGLE_SET_MAP_SIZE];
                if(strcmp(string, myHashMap->values[slotIterator%SHINGLE_SET_MAP_SIZE])==0)
                {
                    return slotIterator%SHINGLE_SET_MAP_SIZE;
                }
            }
            slotIterator++;
        }
    }
}