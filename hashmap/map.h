#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include "vtype.h"

// Define your Map struct here
typedef struct MapStruct Map;

/*Function prototypes*/ 
Map* makeMap(int len);
size_t mapSize(Map* this);
void mapSet(Map* this, VType* key, VType* value);
VType* mapGet(Map* this, VType* key);
_Bool mapRemove(Map* this, VType* key);
void mapFree(Map* this);

#endif // MAP_H

