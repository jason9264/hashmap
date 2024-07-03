#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vtype.h"

/** 
 * @file driver.c
 * @author Jason Wang
 * This program component defines the superclass used to represent strings and integers in the map. 
 * The integer component defines a subclass for storing integers and the text component defines a subclass for storing strings. The implementation file for the vtype component is mostly empty; it provides everything through its header. These components described in the VType Inheritance Hierarchy section below.
 * commands.
*/

/**
 * Creates a new Text object on the heap and returns a pointer to the VType representing it.
 * The function allocates memory for the VType structure and the text content in the 'value.text' field.
 * The text content is copied from the input string 'value' using the 'strdup' function.
 * The 'type' field in the VType structure is set to 'T' to represent a Text object.
 * The caller is responsible for freeing the allocated memory when no longer needed.
 * @param value The input string representing the text content.
 * @return A pointer to the VType representing the created Text object, or NULL on memory allocation failure.
 */
VType* makeText(char* value) {
    VType* v = (VType*)malloc(sizeof(VType));
    if (v) {
        v->type = 'T';
        v->value.text = strdup(value);
    }
    return v;
}

/**
 * Creates a new Integer object on the heap and returns a pointer to the VType representing it.
 * The function allocates memory for the VType structure to store the Integer value.
 * The 'type' field in the VType structure is set to 'I' to represent an Integer object.
 * The Integer value is stored in the 'value.integer' field of the VType structure.
 * The caller is responsible for freeing the allocated memory when no longer needed.
 * @param value The integer value to be stored in the Integer object.
 * @return A pointer to the VType representing the created Integer object, or NULL on memory allocation failure.
 */
VType* makeInteger(int value) {
    VType* v = (VType*)malloc(sizeof(VType));
    if (v) {
        v->type = 'I';
        v->value.integer = value;
    }
    return v;
}

/**
 * Frees the memory occupied by a VType object and its associated data.
 * The function checks the type of the VType object and frees the associated data accordingly.
 * If the VType object represents a Text object, the text content is freed using 'free'.
 * Finally, the memory occupied by the VType object itself is also freed.
 * The caller is responsible for ensuring that the VType object is no longer in use before calling this function.
 * @param v A pointer to the VType object to be freed.
 */
void freeVType(VType* v) {
    if (!v)
        return;

    if (v->type == 'T')
        free(v->value.text);

    free(v);
}

/**
 * Prints the contents of a VType object based on its type.
 * The function checks the type of the VType object and prints the associated data accordingly.
 * If the VType object represents a Text object, the text content is printed using 'printf'.
 * If the VType object represents an Integer object, the integer value is printed using 'printf'.
 * If the provided pointer 'v' is NULL, nothing is printed, and the function returns early.
 * @param v A pointer to the VType object to be printed.
 */
void printVType(const VType* v) {
    if (!v)
        return;

    if (v->type == 'T')
        printf("%s", v->value.text);
    else if (v->type == 'I')
        printf("%d", v->value.integer);
}

/**
 * Checks if two VType objects are equal.
 * The function compares the types and associated data of the two VType objects.
 * If either of the provided pointers 'a' or 'b' is NULL, the function returns false (0).
 * If the types of 'a' and 'b' are different, the function returns false (0).
 * If both VType objects represent Text objects, the text contents are compared using 'strcmp'.
 * If both VType objects represent Integer objects, the integer values are compared.
 * If the VType objects are equal in type and data, the function returns true (1), otherwise, it returns false (0).
 * @param a A pointer to the first VType object to compare.
 * @param b A pointer to the second VType object to compare.
 * @return true (1) if the VType objects are equal, false (0) otherwise.
 */
_Bool equalsVType(const VType* a, const VType* b) {
    if (!a || !b)
        return 0;

    if (a->type != b->type)
        return 0;

    if (a->type == 'T')
        return strcmp(a->value.text, b->value.text) == 0;
    else if (a->type == 'I')
        return a->value.integer == b->value.integer;

    return 0;
}

/**
 * Generates a hash value for a VType object.
 * The function calculates the hash value based on the VType object's type and associated data.
 * If the provided pointer 'v' is NULL, the function returns 0.
 * If the VType object represents a Text object, the hash value is calculated using the djb2 algorithm.
 * If the VType object represents an Integer object, the integer value is converted to a string, and the hash is calculated using djb2.
 * If the VType object's type is neither 'T' nor 'I', the function returns 0 (indicating an unsupported type).
 * @param v A pointer to the VType object for which the hash value is to be calculated.
 * @return The calculated hash value as an unsigned integer, or 0 if the VType object is NULL or has an unsupported type.
 */
unsigned int hashVType(const VType* v) {
    if (!v)
        return 0;

    unsigned int hash = 5381;
    int c;
    char* str;

    if (v->type == 'T')
        str = v->value.text;
    else if (v->type == 'I') {
        char buffer[12];
        sprintf(buffer, "%d", v->value.integer);
        str = buffer;
    } else {
        return 0;
    }

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}