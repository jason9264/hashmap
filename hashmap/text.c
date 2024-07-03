#include "text.h"
#include <stdlib.h>
#include <string.h>
#include "vtype.h" 
#include "stdio.h" 

/** 
 * @file integer.c
 * @author Jason Wang
 * This program is a subclasses of VType, Integer for storing integer values and Text for storing string values.
*/

/**
 * Text struct representing a custom data type to store text information.
 * The struct includes a parent field of type VType to store the common VType fields.
 * The 'data' field is a pointer to a character array representing the text content.
 * The 'length' field stores the number of characters in the text.
 */

struct Text {
    VType parent; // Add a parent field of type VType to store the common VType fields
    char* data;
    int length;
};

/**
 * Parses a text from the input string and creates a Text object on the heap with the parsed content.
 * The input string is expected to contain a text terminated by a tab or newline character or the end of the string.
 * The function allocates memory for the Text object and its 'data' field, which contains the parsed text.
 * If parsing is successful, the function returns a pointer to the Text object with the parsed content.
 * If parsing fails or memory allocation fails, the function returns NULL.
 * The caller can provide an optional pointer 'n' to obtain the number of characters parsed from the input string.
 * The caller is responsible for freeing the allocated memory when no longer needed.
 * @param init The input string to be parsed as a text.
 * @param n A pointer to an integer where the number of characters parsed will be stored (optional).
 * @return A pointer to the Text object with the parsed content, or NULL on parsing or memory allocation failure.
 */
Text* parseText(const char* init, int* n) {
    Text* this = (Text*)malloc(sizeof(Text));
    if (!this)
        return NULL;

    // Find the length of the initialization string up to the next tab or newline.
    int i = 0;
    while (init[i] != '\0' && init[i] != '\t' && init[i] != '\n')
        i++;

    // Allocate memory for the data and copy the text from the initialization string.
    this->data = (char*)malloc((i + 1) * sizeof(char));
    if (!this->data) {
        free(this);
        return NULL;
    }

    strncpy(this->data, init, i);
    this->data[i] = '\0';
    this->length = i;

    if (n)
        *n = i; // Set n to the location after the parsed text.

    return this;
}

/**
 * Retrieves the length of the Text content.
 * @param this A pointer to the Text object.
 * @return The number of characters in the Text content.
 */
int textLength(const Text* this) {
    return this->length;
}

/**
 * Retrieves the character at the specified index in the Text content.
 * If the index is within the valid range (0 to (length - 1)), the corresponding character is returned.
 * If the index is outside the valid range, the function returns the null character ('\0').
 * @param this A pointer to the Text object.
 * @param index The index of the character to retrieve.
 * @return The character at the specified index, or the null character ('\0') if the index is invalid.
 */
char textCharAt(const Text* this, int index) {
    if (index >= 0 && index < this->length)
        return this->data[index];
    return '\0'; // Invalid index, return null character.
}

/**
 * Checks if two Text objects are equal.
 * The function compares the content of the Text objects.
 * If the Text objects have the same address, they are considered equal.
 * If the Text objects have different lengths, they are considered not equal.
 * If the content of the Text objects is the same (same characters in the same order), they are considered equal.
 * @param this A pointer to the first Text object to compare.
 * @param other A pointer to the second Text object to compare.
 * @return true if the Text objects are equal, false otherwise.
 */
bool textEquals(const Text* this, const Text* other) {
    if (this == other)
        return true;

    if (this->length != other->length)
        return false;

    return strcmp(this->data, other->data) == 0;
}

/**
 * Frees the memory occupied by the Text object.
 * The function deallocates memory for the 'data' field and the Text object itself.
 * The caller is responsible for ensuring that the Text object is no longer in use before calling this function.
 * @param this A pointer to the Text object to be destroyed.
 */
void textDestroy(Text* this) {
    if (this) {
        free(this->data);
        free(this);
    }
}

/**
 * Print method for Text.
 * The function is used to print the content of the Text object.
 * It converts the VType pointer to a more specific type (Text) and prints the text content with a newline character.
 * The newline character is added to flush the output after printing the Text content.
 * @param v A pointer to the VType object representing the Text to be printed.
 */
static void printText(VType const* v) {
    // Convert the VType pointer to a more specific type.
    Text const* this = (Text const*)v;
    printf("%s\n", this->data); // Add a newline character to flush the output
}

/**
 * Creates a new Text object on the heap and fills in its fields with the provided text content.
 * The function allocates memory for the Text object and its 'data' field, which contains the text content.
 * The text content is copied from the input string 'value' to the 'data' field of the Text object.
 * The Text object also includes parent fields of type VType for compatibility with the VType interface.
 * The returned pointer is a pointer to the VType, representing the Text object.
 * Memory allocated for the Text object and the 'data' field should be freed by the caller when no longer needed.
 * @param value The input string representing the text content.
 * @return A pointer to the VType, representing the created Text object, or NULL on memory allocation failure.
 */
VType* makeText(char const* value) {
    // Allocate a Text object on the heap and fill in its fields.
    Text* this = (Text*)malloc(sizeof(Text));
    if (!this)
        return NULL;

    /* Initialize the VType fields
    this->parent.print = print;
    this->parent.equals = equals;
    this->parent.hash = hash;
    this->parent.destroy = destroy;
*/
    // Allocate memory for the data and copy the text from the initialization string.
    int length = strlen(value);
    this->data = (char*)malloc((length + 1) * sizeof(char));
    if (!this->data) {
        free(this);
        return NULL;
    }

    strcpy(this->data, value);
    this->length = length;

    // Return it as a pointer to the superclass.
    return (VType*)this;
}

