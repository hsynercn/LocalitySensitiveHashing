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
        myHashMap->keys[i] = -1;
    }
    
    for(int i=0;i<myHashMap->hashMapSize;i++)
    {
        printf(">slt:%d k:%d v:%s\n",i,myHashMap->keys[i],myHashMap->values[i]);
    }
    return myHashMap;
}