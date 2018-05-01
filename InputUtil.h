#ifndef INPUTUTIL_H_
#define INPUTUTIL_H_

#define INVALID_CHAR '.'

void readInputFile(char *fineName, long int *outputTextSize, char **outputBufferPointer);
long int countExtraBlanks(long int textSize, char *textBuffer);
char chechCharValidty(char checkChar);
long int getValidCharCount(long int textSize, char *textBuffer);
void removeInvalidChars(long int textSize, char *textBuffer, long int *validTextSize, char **validBufferPointer);
void removeExtraBlanks(long int validCharCount, char *validBuffer, long int reducedTextSize, char **reducedBufferPointer);
void formatInputText(long int textSize, char *textBuffer, long int *filteredTextSize, char **filteredBufferPointer);
#endif

