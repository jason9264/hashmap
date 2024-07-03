#include <stdio.h>
#include "map.h"

int main() {
    Map* map = makeMap(3);

    mapSet(map, makeText("key1"), makeInteger(42));
    mapSet(map, makeText("key2"), makeInteger(123));
    mapSet(map, makeText("key3"), makeText("hello"));

    printf("Size: %zu\n", mapSize(map));

    VType* value = mapGet(map, makeText("key1"));
    if (value) {
        printf("Value: ");
        printVType(value);
        printf("\n");
    } else {
        printf("Key not found.\n");
    }

    mapRemove(map, makeText("key2"));

    printf("Size: %zu\n", mapSize(map));

    value = mapGet(map, makeText("key2"));
    if (value) {
        printf("Value: ");
        printVType(value);
        printf("\n");
    } else {
        printf("Key not found.\n");
    }

    mapFree(map);

    return 0;
}

