// text.h
#ifndef TEXT_H
#define TEXT_H

#include "vtype.h"

/** Structure to represent a Text object */
typedef struct {
    char* str; // Pointer to the string content
    void (*print)(VType const* v);      // Function to print the Text
    bool (*equals)(VType const* a, VType const* b);  // Function to compare two Texts
    unsigned int (*hash)(VType const* v);  // Function to calculate the hash code for a Text
    void (*destroy)(VType* v);  // Function to free the memory used by a Text
} Text;

/** Create a new Text object by parsing the initialization value from a string.
    @param init String containing the initialization value as text.
    @param n Optional return for the number of characters used from init.
    @return Pointer to the new VType instance (Text object).
*/
VType* parseText(char const* init, int* n);

#endif

