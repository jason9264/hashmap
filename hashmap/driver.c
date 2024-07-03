#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 
 * @file driver.c
 * @author Jason Wang
 * This program Using the other components, it reads and processes commands from standard input, updates the map as needed and prints responses to user
 * commands.
*/

#define TABLE_SIZE 100

typedef struct {
    int key;
    char *value;
} Entry;

Entry *table[TABLE_SIZE];

/**
 * This function calculates the hash value for the given key using the modulo operator.
 * The hash value is used to map the key to an index in the hash table.
 * @param key the integer key for which the hash value needs to be calculated
 * @return the calculated hash value (an index in the hash table)
 */
int hash(int key) {
    return key % TABLE_SIZE;
}

/**
 * This function sets a key-value pair in the hashmap by calculating the index using the hash function.
 * If the key already exists in the hashmap, the existing value is updated with the new value.
 * If the key does not exist, a new entry is created and added to the hashmap.
 * Note: The function assumes that the hashmap, `table`, is already initialized and has enough space.
 * @param key the integer key for the key-value pair
 * @param value a pointer to the C string (null-terminated) representing the value associated with the key
 */
void set(int key, const char *value) {
    int index = hash(key);

    while (table[index] != NULL) {
        if (table[index]->key == key) {
            free(table[index]->value);
            table[index]->value = strdup(value);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
    }

    Entry *new_entry = malloc(sizeof(Entry));
    new_entry->key = key;
    new_entry->value = strdup(value);

    table[index] = new_entry;
}

/**
 * This function retrieves the value associated with the given key from the hashmap.
 * If the key is found in the hashmap, a pointer to the corresponding value is returned.
 * If the key is not found, NULL is returned.
 * Note: The function assumes that the hashmap, `table`, is already initialized.
 * @param key the integer key for which the value needs to be retrieved
 * @return a pointer to the C string (null-terminated) representing the value associated with the key, or NULL if the key is not found
 */
char *get(int key) {
    int index = hash(key);

    while (table[index] != NULL) {
        if (table[index]->key == key) {
            return table[index]->value;
        }
        index = (index + 1) % TABLE_SIZE;
    }

    return NULL;
}

// Remove a key-value pair from the hashmap
void remove_entry(int key) {
    int index = hash(key);

    while (table[index] != NULL) {
        if (table[index]->key == key) {
            free(table[index]->value);
            free(table[index]);
            table[index] = NULL;
            return;
        }
        index = (index + 1) % TABLE_SIZE;
    }
}

/**
 * This function removes a key-value pair from the hashmap based on the provided key.
 * If the key is found in the hashmap, the corresponding entry is removed, and memory allocated for the entry's value and the entry itself is freed.
 * If the key is not found, the function does nothing and simply returns.
 * Note: The function assumes that the hashmap, `table`, is already initialized.
 * @param key the integer key for the key-value pair to be removed
 */
void free_map() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {
            free(table[i]->value);
            free(table[i]);
        }
    }
}

/**
 * Returns the number of key-value pairs in the hashmap.
 * @return The number of key-value pairs.
 */
int size() {
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {
            count++;
        }
    }
    return count;
}

/**
 * Main loop for a command-line interface (CLI) with a hashmap.
 * Supports commands: set, get, remove, size, quit.
 * CLI continues until 'quit' command is entered.
 * Note: Functions 'set', 'get', 'remove_entry', and 'free_map' should be defined elsewhere.
 * Assumes hashmap 'table' is initialized and has enough space.
 * @return Exit status: 0 for success, non-zero for errors.
 */
int main() {
    char cmd[20];
    int key, value;
    char input[100];

    while (1) {
        printf("cmd> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        if (sscanf(input, "%19s", cmd) != 1) {
            printf("Invalid command.\n");
            continue;
        }

        if (strcmp(cmd, "set") == 0) {
            if (sscanf(input, "%*s %d %d", &key, &value) != 2) {
                printf("Invalid 'set' command format.\n");
                continue;
            }
            set(key, input + strlen(cmd) + 4); // +4 accounts for spaces and key
        } else if (strcmp(cmd, "get") == 0) {
            if (sscanf(input, "%*s %d", &key) != 1) {
                printf("Invalid 'get' command format.\n");
                continue;
            }
            char *result = get(key);
            if (result)
                printf("%s\n", result);
            else
                printf("Key not found.\n");
        } else if (strcmp(cmd, "remove") == 0) {
            if (sscanf(input, "%*s %d", &key) != 1) {
                printf("Invalid 'remove' command format.\n");
                continue;
            }
            remove_entry(key);
        } else if (strcmp(cmd, "size") == 0) {
            int num_keys = size();
            printf("%d\n\n", num_keys);
        } else if (strcmp(cmd, "quit") == 0) {
            break;
        } else {
            printf("Unknown command.\n");
        }
    }

    free_map();
    return 0;
}
