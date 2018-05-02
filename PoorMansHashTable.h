#ifndef POORMANSHASHTABLE_H_
#define POORMANSHASHTABLE_H_

#define SHINGLE_SET_MAP_SIZE 1489
#define SHINGLE_MAX_STR_LEN 9
#define EMPTY_CHAR '.'
#define EMPTY_KEY -1
#define CANT_INSERT_LONG_STR -1
#define CANT_INSERT_VALUE_IN_SET -2
#define CANT_INSERT_MAP_FULL -3
#define CANT_INSERT_UNKOWN_ERROR -4


/*
 * Map has the keys, it is not mandotary at the time but
 * it helps the insertion traceing and segment shift monitoring*/
typedef struct MY_HASH_MAP{
  int long hashMapSize;
  char **values;
  int *keys;
};

struct MY_HASH_MAP *newMyHashMap();
int strLen(char* string);
long int stringToNum(char* string);
int long insert(char* string, struct MY_HASH_MAP *myHashMap);

#endif