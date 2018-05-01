#include <stdio.h>
#include <stdlib.h>
#include "InputUtil.h"
#include "PoorMansHashTable.h"



int main(int argc, char **argv)
{
    
    char *fileName = "D:/C-C++/SandBox/LocalitySensitiveHashing/Sample.txt";
    long int outputTextSize = 0;
    char temp = 't';
    char *outputBuffer = &temp;
    char **outputBufferPointer = &outputBuffer;
    
    readInputFile(fileName, &outputTextSize, outputBufferPointer);

    if(outputTextSize == -1)
    {
        printf("Program execution halted due to invalid input string.");
    }
    
    //outputBuffer = *outputBufferPointer;
    
    long int filteredTextSize = 0;
    char temp2 = 't';
    char *filteredBuffer = &temp2;
    char **filteredBufferPointer = &filteredBuffer;
    
    formatInputText(outputTextSize, outputBuffer, &filteredTextSize, filteredBufferPointer);
    
    printf("text size: %lu\n", filteredTextSize);
    
    struct MY_HASH_MAP *shingleSet = newMyHashMap();
    
    
    return 0;
}
