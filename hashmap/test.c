#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <input.c>

// Structure to represent a generic value in the VType
typedef struct {
    void* value;
    enum { INT, STRING } type;
} VType;

// Structure to represent an integer VType
typedef struct {
    int value;
} Integer;

// Function to create a new Integer VType
VType* createInteger(int value) {
    Integer* integer = (Integer*)malloc(sizeof(Integer));
    if (!integer) {
        perror("Error: Unable to allocate memory for Integer VType");
        exit(EXIT_FAILURE);
    }

    integer->value = value;

    VType* vtype = (VType*)malloc(sizeof(VType));
    if (!vtype) {
        perror("Error: Unable to allocate memory for VType");
        free(integer);
        exit(EXIT_FAILURE);
    }

    vtype->value = integer;
    vtype->type = INT;
    return vtype;
}

// Structure to represent a text VType
typedef struct {
    char* value;
} Text;

// Function to create a new Text VType
VType* createText(const char* value) {
    Text* text = (Text*)malloc(sizeof(Text));
    if (!text) {
        perror("Error: Unable to allocate memory for Text VType");
        exit(EXIT_FAILURE);
    }

    text->value = strdup(value);

    VType* vtype = (VType*)malloc(sizeof(VType));
    if (!vtype) {
        perror("Error: Unable to allocate memory for VType");
        free(text->value);
        free(text);
        exit(EXIT_FAILURE);
    }

    vtype->value = text;
    vtype->type = STRING;
    return vtype;
}

// Function to print the value
void printVType(VType* v) {
    if (v) {
        switch (v->type) {
            case INT:
                printf("%d", ((Integer*)v->value)->value);
                break;
            case STRING:
                printf("%s", ((Text*)v->value)->value);
                break;
        }
    }
}

// Function to destroy the VType and free memory
void destroyVType(VType* v) {
    if (v) {
        switch (v->type) {
            case INT:
                free(v->value);
                break;
            case STRING:
                free(((Text*)v->value)->value);
                break;
        }
        free(v);
    }
}

// Entry structure for the Map
typedef struct Entry Entry;

struct Entry {
    char* key;
    VType* value;
    Entry* next;
};

// Map structure
typedef struct {
    int capacity;
    int size;
    Entry** table;
} Map;

// Hash function for string keys
unsigned int hashString(char* str, int capacity) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash % capacity;
}

// Function to create a new Map
Map* makeMap(int capacity) {
    Map* map = (Map*)malloc(sizeof(Map));
    if (!map) {
        perror("Error: Unable to allocate memory for Map");
        exit(EXIT_FAILURE);
    }

    map->capacity = capacity;
    map->size = 0;
    map->table = (Entry**)calloc(capacity, sizeof(Entry*));
    if (!map->table) {
        perror("Error: Unable to allocate memory for Map Table");
        free(map);
        exit(EXIT_FAILURE);
    }

    return map;
}

// Function to set a key-value pair in the map
void mapSet(Map* map, char* key, VType* value) {
    if (!map || !key || !value)
        return;

    unsigned int index = hashString(key, map->capacity);

    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    if (!new_entry) {
        perror("Error: Unable to allocate memory for Map Entry");
        exit(EXIT_FAILURE);
    }

    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = NULL;

    // Handle the collision by chaining
    Entry* entry = map->table[index];
    if (!entry) {
        map->table[index] = new_entry;
    } else {
        while (entry->next)
            entry = entry->next;
        entry->next = new_entry;
    }

    map->size++;
}

// Function to get the value associated with a key from the map
VType* mapGet(Map* map, char* key) {
    if (!map || !key)
        return NULL;

    unsigned int index = hashString(key, map->capacity);
    Entry* entry = map->table[index];

    while (entry) {
        if (strcmp(entry->key, key) == 0)
            return entry->value;
        entry = entry->next;
    }

    return NULL;
}

// Function to remove a key-value pair from the map
bool mapRemove(Map* map, char* key) {
    if (!map || !key)
        return false;

    unsigned int index = hashString(key, map->capacity);
    Entry* entry = map->table[index];
    Entry* prev = NULL;

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev)
                prev->next = entry->next;
            else
                map->table[index] = entry->next;

            free(entry->key);
            destroyVType(entry->value);
            free(entry);
            map->size--;
            return true;
        }
        prev = entry;
        entry = entry->next;
    }

    return false;
}

// Function to get the size of the map
int mapSize(Map* map) {
    return map ? map->size : -1;
}

// Function to free an entry in the map
void freeEntry(Entry* entry) {
    if (entry) {
        free(entry->key);
        destroyVType(entry->value);
        free(entry);
    }
}

// Function to free the map and its entries
void mapFree(Map* map) {
    if (!map)
        return;

    for (int i = 0; i < map->capacity; i++) {
        Entry* entry = map->table[i];
        while (entry) {
            Entry* temp = entry;
            entry = entry->next;
            freeEntry(temp);
        }
    }

    free(map->table);
    free(map);
}

/** Maximum length for a command name. */
#define MAX_CMD 10

/**
   Starting point for the program.
   @return exit status for the program.
 */
int main() {
    // Make our map, with a 100-element table.
    Map* map = makeMap(100); // For text values

    // Keep reading input from the user.
    char* line;
    printf("cmd> ");
    while ((line = readLine(stdin))) {
        // Echo the command back to the user.
        printf("%s\n", line);

        // Extract the first word from the command.
        bool valid = false;
        char cmd[MAX_CMD + 1];
        int n;
        if (sscanf(line, "%10s%n", cmd, &n) == 1) {
            // Pos keeps up with where we are in parsing the command.
            char* pos = line + n;
            if (strcmp(cmd, "get") == 0) {
                // Parse the key from the command.
                char key[MAX_CMD + 1];
                if (sscanf(pos, "%10s", key) == 1) {
                    pos += strlen(key);

                    // Make sure there's nothing extra in the command.
                    if (isspace(*pos) || *pos == '\0') {
                        valid = true;
                        VType* value = mapGet(map, key);
                        if (value) {
                            printf("Value: ");
                            printVType(value);
                            printf("\n");
                        } else {
                            printf("Key not found\n");
                        }
                    }
                }
            } else if (strcmp(cmd, "set") == 0) {
                // Parse the key from the command.
                char key[MAX_CMD + 1];
                if (sscanf(pos, "%10s%n", key, &n) == 1) {
                    pos += n;

                    // Parse the value from the command.
                    VType* value = parseVType(pos, &n);
                    if (value) {
                        pos += n;

                        // Make sure there's nothing extra in the command.
                        if (isspace(*pos) || *pos == '\0') {
                            valid = true;
                            mapSet(map, key, value);
                        } else {
                            destroyVType(value);
                        }
                    }
                }
            } else if (strcmp(cmd, "remove") == 0) {
                // Parse the key from the command.
                char key[MAX_CMD + 1];
                if (sscanf(pos, "%10s%n", key, &n) == 1) {
                    pos += n;

                    // Make sure there's nothing extra in the command.
                    if (isspace(*pos) || *pos == '\0') {
                        valid = true;
                        if (!mapRemove(map, key))
                            printf("Key not found\n");
                    }
                }
            } else if (strcmp(cmd, "mapfree") == 0) {
                // Make sure there's nothing extra in the command.
                if (isspace(*pos) || *pos == '\0') {
                    // Free the map before exiting.
                    mapFree(map);
                    printf("Map freed\n");
                    exit(EXIT_SUCCESS);
                }
            }
        }

        // Print a message if we didn't get a valid command.
        if (!valid) {
            printf("Invalid command\n");
        }

        // Free the last command and prompt for another one.
        free(line);
        printf("\ncmd> ");
    }

    // Free the map before exiting.
    mapFree(map);
    return EXIT_SUCCESS;
}

