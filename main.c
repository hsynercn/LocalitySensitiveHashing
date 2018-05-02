#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputUtil.h"
#include "PoorMansHashTable.h"
#include "ShingleUtil.h"

int main(int argc, char **argv)
{
    struct MY_HASH_MAP *shingleSetA = generateKShingleSetOfFile("D:/C-C++/Git/LocalitySensitiveHashing/SampleA.txt", 4);
    dumpHashMap(shingleSetA);
    
    struct MY_HASH_MAP *shingleSetB = generateKShingleSetOfFile("D:/C-C++/Git/LocalitySensitiveHashing/SampleB.txt", 4);
    dumpHashMap(shingleSetB);
    
    long int filledA = countFilledSlots(shingleSetA);
    long int filledB = countFilledSlots(shingleSetB);
    long int common = commonShingleCount(shingleSetB, shingleSetA);
    float jaccard = jaccardSimilarity(shingleSetB, shingleSetA);
    return 0;
}
