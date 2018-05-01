#ifndef POORMANSHASHTABLE_H_
#define POORMANSHASHTABLE_H_

#define SHINGLE_SET_MAP_SIZE 1489
#define SHINGLE_MAX_STR_LEN 9
#define EMPTY_CHAR '.'

typedef struct MY_HASH_MAP{
  int long hashMapSize;
  char **values;
  int *keys;
};

struct MY_HASH_MAP *newMyHashMap();

#endif