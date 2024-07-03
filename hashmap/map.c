#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define TABLE_SIZE 1024

/** 
 * @file map.c
 * @author Jason Wang
 * This program provides an implementation of the map as a hash table. 
 */

/**
 * Node struct for creating linked list elements to store key-value pairs.
 * Each node contains pointers to the key and value (VType objects) and a pointer to the next node in the linked list.
 */
typedef struct NodeStruct {
    VType* key;
    VType* value;
    struct NodeStruct* next;
} Node;

/**
 * MapStruct for creating a hashmap data structure.
 * The MapStruct contains an array of Node pointers (table) to store key-value pairs in a hash table format.
 * It also keeps track of the number of key-value pairs stored (size).
 */
struct MapStruct {
    Node* table[TABLE_SIZE];
    size_t size;
};

/**
 * Hashes the given VType key to calculate the index in the hashmap's table.
 * The hashing is performed using the 'hashVType' function on the key and then taking the modulo TABLE_SIZE.
 * @param this A pointer to the Map structure (hashmap).
 * @param key A pointer to the VType object representing the key to be hashed.
 * @return The index in the hashmap's table where the key-value pair will be stored.
 */
static unsigned int hash(Map* this, VType* key) {
    return hashVType(key) % TABLE_SIZE;
}

/**
 * Creates a new Map (hashmap) on the heap and initializes its fields.
 * The Map is represented by an array of NULL pointers (table) to store key-value pairs in a hash table format.
 * The initial size of the Map is specified by the 'len' parameter.
 * The returned Map pointer can be used to interact with the Map.
 * Memory allocated for the Map should be freed by the caller when no longer needed.
 * @param len The initial size of the Map (number of buckets in the hashmap).
 * @return A pointer to the Map structure, representing the created hashmap, or NULL on memory allocation failure.
 */
Map* makeMap(int len) {
    Map* map = (Map*)malloc(sizeof(Map));
    if (map) {
        for (int i = 0; i < TABLE_SIZE; i++)
            map->table[i] = NULL;
        map->size = len;
    }
    return map;
}

/**
 * Retrieves the current size of the Map (number of key-value pairs stored).
 * @param this A pointer to the Map structure (hashmap).
 * @return The number of key-value pairs stored in the Map.
 */
size_t mapSize(Map* this) {
    return this->size;
}

/**
 * Sets a key-value pair in the Map (hashmap).
 * The key-value pair is associated with a specific bucket determined by the hash of the key.
 * If the key already exists in the hashmap, the existing value is replaced with the new value.
 * If the key does not exist, a new Node is created and added to the corresponding bucket in the hashmap.
 * The function uses the 'hash' function to calculate the index in the hashmap's table for the key.
 * The function uses the 'equalsVType' function to check for key equality in the hashmap.
 * The caller is responsible for memory management of the VType objects.
 * @param this A pointer to the Map structure (hashmap).
 * @param key A pointer to the VType object representing the key.
 * @param value A pointer to the VType object representing the value associated with the key.
 */
void mapSet(Map* this, VType* key, VType* value) {
    int index = hash(this, key) % TABLE_SIZE;
    Node* node = this->table[index];
    while (node) {
        if (equalsVType(node->key, key)) {
            freeVType(node->value);
            node->value = value;
            return;
        }
        node = node->next;
    }

    node = (Node*)malloc(sizeof(Node));
    if (node) {
        node->key = key;
        node->value = value;
        node->next = this->table[index];
        this->table[index] = node;
    }
}

/**
 * Retrieves the value associated with the given key from the Map (hashmap).
 * The function searches for the key in the corresponding bucket, determined by the hash of the key.
 * If the key is found in the hashmap, the associated value is returned.
 * If the key is not found, the function returns NULL.
 * The function uses the 'hash' function to calculate the index in the hashmap's table for the key.
 * The function uses the 'equalsVType' function to check for key equality in the hashmap.
 * @param this A pointer to the Map structure (hashmap).
 * @param key A pointer to the VType object representing the key to be retrieved.
 * @return A pointer to the VType object representing the value associated with the key, or NULL if the key is not found.
 */
VType* mapGet(Map* this, VType* key) {
    int index = hash(this, key) % TABLE_SIZE;
    Node* node = this->table[index];
    while (node) {
        if (equalsVType(node->key, key))
            return node->value;
        node = node->next;
    }
    return NULL;
}

/**
 * Removes the key-value pair associated with the given key from the Map (hashmap).
 * The function searches for the key in the corresponding bucket, determined by the hash of the key.
 * If the key is found in the hashmap, the associated key-value pair is removed.
 * Memory allocated for the removed key and value (VType objects) is freed.
 * The function uses the 'hash' function to calculate the index in the hashmap's table for the key.
 * The function uses the 'equalsVType' function to check for key equality in the hashmap.
 * @param this A pointer to the Map structure (hashmap).
 * @param key A pointer to the VType object representing the key to be removed.
 * @return 1 if the key-value pair is successfully removed, 0 otherwise (key not found).
 */

_Bool mapRemove(Map* this, VType* key) {
    int index = hash(this, key) % TABLE_SIZE;
    Node* prev = NULL;
    Node* node = this->table[index];
    while (node) {
        if (equalsVType(node->key, key)) {
            if (prev)
                prev->next = node->next;
            else
                this->table[index] = node->next;
            freeVType(node->key);
            freeVType(node->value);
            free(node);
            this->size--;
            return 1;
        }
        prev = node;
        node = node->next;
    }
    return 0;
}

/**
 * Frees the memory occupied by the Map (hashmap) and all its key-value pairs.
 * The function iterates through the hashmap's table and deallocates memory for each key-value pair.
 * Memory allocated for the Map and all its nodes (key-value pairs) is freed.
 * The caller is responsible for ensuring that the Map and all its keys and values are no longer in use.
 * @param this A pointer to the Map structure (hashmap) to be freed.
 */
void mapFree(Map* this) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = this->table[i];
        while (node) {
            Node* temp = node;
            node = node->next;
            freeVType(temp->key);
            freeVType(temp->value);
            free(temp);
        }
    }
    free(this);
}

