#include "InputUtil.h"
#include <stdio.h>
#include <stdlib.h>

void readInputFile(char *fineName, long int *outputTextSize, char **outputBufferPointer)
{
    char *buffer = NULL;
    long int size = 0;
    FILE *fp = fopen(fineName, "r");
    
    if (fp == NULL) 
    {
        printf("Input file is not valid!\n");
        *outputTextSize = -1;
        *outputBufferPointer = NULL;
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    rewind(fp);
    buffer = malloc((size) * sizeof(char));
    fread(buffer, size, 1, fp);
    
    *outputTextSize = size;
    *outputBufferPointer = buffer;
    return;
}

long int countExtraBlanks(long int textSize, char *textBuffer)
{
    char previous = *textBuffer;
    textBuffer=textBuffer+sizeof(char);
    long int extraBlankCount = 0;
    for(long int i=1;i<textSize;i++)
    {
        if(previous == ' ' && *textBuffer == ' ')
        {
            extraBlankCount++;
        }
        previous = *textBuffer;
        textBuffer = textBuffer+sizeof(char);
    }
    return extraBlankCount;
}

char chechCharValidty(char checkChar)
{
    if(checkChar>='a' && checkChar<='z')
        return checkChar;
    if(checkChar>='A' && checkChar<='Z')
        return checkChar + ('a' - 'A') ;
    if(checkChar==' ')
        return checkChar;

    return INVALID_CHAR;
}

long int getValidCharCount(long int textSize, char *textBuffer)   
{
    char *textIteratorPointer = textBuffer;
    
    long int validCharCount = 0;
    for(long int i=0;i<textSize;i++)
    {
        if(chechCharValidty(*textIteratorPointer)!=INVALID_CHAR)
        {
            validCharCount++;
        }
        textIteratorPointer=textIteratorPointer+sizeof(char);
    }
    return validCharCount;
}

void removeInvalidChars(long int textSize, char *textBuffer, long int *validTextSize, char **validBufferPointer)  
{
    long int validCharCount = getValidCharCount( textSize, textBuffer);
    
    char *textIteratorPointer = textBuffer;
    char *bufferValid = NULL;
    bufferValid = malloc((validCharCount) * sizeof(char));
    
    textIteratorPointer = textBuffer;

    long int locatedCharCount = 0;
    for(long int i=0;i<textSize;i++)
    {
        char temp = chechCharValidty(*textIteratorPointer);
        if(temp!=INVALID_CHAR)
        {
            bufferValid[locatedCharCount] = temp;
            locatedCharCount++;
        }
        textIteratorPointer=textIteratorPointer+sizeof(char);
    }
    
    *validTextSize = locatedCharCount;
    *validBufferPointer = bufferValid;
}

void removeExtraBlanks(long int validCharCount, char *validBuffer, long int reducedTextSize, char **reducedBufferPointer) 
{
    char *bufferReduced = NULL;
    bufferReduced = malloc((reducedTextSize) * sizeof(char));
    
    char *bufferReducedIterator = bufferReduced;
    char *textIteratorPointer = validBuffer;
    char previous = *textIteratorPointer;
    
    long int reducedSizeCounter = 0;
    
    for(long int i=1;i<validCharCount;i++)
    {
        if(previous == ' ' && *textIteratorPointer == ' ')
        {
            //skip
        }
        else
        {
           *bufferReducedIterator = *textIteratorPointer;
           bufferReducedIterator=bufferReducedIterator+sizeof(char);
        }
        previous = *textIteratorPointer;
        textIteratorPointer=textIteratorPointer+sizeof(char);
        reducedSizeCounter++;
    }
    
    *reducedBufferPointer = bufferReduced;
}

void formatInputText(long int textSize, char *textBuffer, long int *filteredTextSize, char **filteredBufferPointer)    
{
    long int validTextSize = 0;
    char temp = 't';
    char *validBuffer = &temp;
    char **validBufferPointer = &validBuffer;
    
    removeInvalidChars(textSize,textBuffer, &validTextSize, validBufferPointer);
    
    int validCharCount = validTextSize;
    
    long int extraBlankCount = countExtraBlanks(validCharCount, validBuffer);
    
    long int reducedTextSize = validCharCount - extraBlankCount;
    char temp2 = 't';
    char *reducedBuffer = &temp2;
    char **reducedBufferPointer = &reducedBuffer;
    
    removeExtraBlanks(validCharCount, validBuffer, reducedTextSize, reducedBufferPointer);

    *filteredTextSize = reducedTextSize;
    *filteredBufferPointer = reducedBuffer;
    free(validBuffer);
    return;
}