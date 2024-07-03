#include "input.h"
#include <stdlib.h>

/** 
 * @file input.c
 * @author Jason Wang
 * This program read commands from the user a line at a time, decide if they are valid and discard the whole input line if they're not.
*/

/**
 * Reads a line from the specified file and returns it as a dynamically allocated C string.
 * The function allocates memory for the string and automatically resizes it as needed.
 * The returned string is null-terminated and should be freed by the caller when no longer needed.
 * @param fp A pointer to the file from which the line is to be read.
 * @return A dynamically allocated C string containing the read line, or NULL on failure or end of file.
 */
char* readLine(FILE* fp) {
    // Check if the file pointer is valid
    if (!fp)
        return NULL;

    int capacity = 16; // Initial capacity of the dynamic array
    int size = 0;      // Number of characters read
    char* line = (char*)malloc(capacity * sizeof(char));

    // Check if memory allocation is successful
    if (!line)
        return NULL;

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            line[size++] = '\0'; // Null-terminate the string
            return line;
        }

        line[size++] = ch;

        // Resize the array if needed
        if (size >= capacity) {
            capacity *= 2;
            char* newLine = (char*)realloc(line, capacity * sizeof(char));
            if (!newLine) {
                free(line);
                return NULL;
            }
            line = newLine;
        }
    }

    // If no more input to read, return NULL
    if (size == 0) {
        free(line);
        return NULL;
    }

    // Null-terminate the string
    line[size] = '\0';
    return line;
}

