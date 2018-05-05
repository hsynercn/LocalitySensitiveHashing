#ifndef SHINGLEUTIL_H_
#define SHINGLEUTIL_H_

#define SIGNATURE_LENGTH 100

struct MY_HASH_MAP *generateKShingleSet(long int stringLen, char* string, int k);
struct MY_HASH_MAP *generateKShingleSetOfFile(char *fileName, int k);
long int commonShingleCount( struct MY_HASH_MAP *shingleSetA,  struct MY_HASH_MAP *shingleSetB);
float jaccardSimilarity(struct MY_HASH_MAP *shingleSetA,  struct MY_HASH_MAP *shingleSetB);
int getUnifiedSetCount(struct MY_HASH_MAP *shingleSetA, struct MY_HASH_MAP *shingleSetB);
int *initilizeSignatureHashConstants(int singatureLen, int valueLimit);
#endif