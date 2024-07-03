/**
    @file integer.c
    @author CSC 230
    Implementation of the Integer VType.


#include "integer.h"

#include <stdio.h>
#include <stdlib.h>

// print method for Integer.
static void print(VType const* v) {
    // Convert the VType pointer to a more specific type.
    Integer const* this = (Integer const*)v;
    printf("%d", this->val);
}

// equals method for Integer.
static bool equals(VType const* a, VType const* b) {
    // Make sure the b object is also an Integer.
    // (i.e., it uses the same print funtion)
    if (b->print != print)
        return false;

    // Compare the val fields inside a and b.
    Integer const* this = (Integer const*)a;
    Integer const* that = (Integer const*)b;

    return this->val == that->val;
}

// hash method for Integer.  It hashes to the int value it contains,
// with negative values overflowing to positive.
static unsigned int hash(VType const* v) {
    // Convert the VType pointer to a more specific type.
    Integer const* this = (Integer const*)v;
    // This will overflow negative values to large positive ones.
    return this->val;
}

// destroy method for Integer.
static void destroy(VType* v) {
    // Integer is just one block of heap memory.
    free(v);
}

VType* parseInteger(char const* init, int* n) {
    // Make sure the string is in the right format.
    int val, len;
    if (sscanf(init, "%d%n", &val, &len) != 1) {
        return NULL;
    }

    // Fill in the end pointer, if the caller asked for it.
    if (n)
        *n = len;

    // Allocate an Integer on the heap and fill in its fields.
    Integer* this = (Integer*)malloc(sizeof(Integer));
    this->val = val;
    this->print = print;
    this->equals = equals;
    this->hash = hash;
    this->destroy = destroy;

    // Return it as a poitner to the superclass.
    return (VType*)this;
}
*/

#include "integer.h"
#include "vtype.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints the integer value stored in the given Integer object.
 * This function is specific to the Integer type and requires casting from the base VType pointer.
 * @param v A pointer to the VType object, representing an Integer.
 */
static void print(VType const* v) {
    // Convert the VType pointer to a more specific type.
    Integer const* this = (Integer const*)v;
    printf("%d", this->val);
}

/**
 * Checks if two Integer objects are equal by comparing their integer values.
 * This function is specific to the Integer type and requires casting from the base VType pointers.
 * @param a A pointer to the VType object, representing the first Integer.
 * @param b A pointer to the VType object, representing the second Integer.
 * @return true if the Integer objects are equal (have the same integer value), false otherwise.
 */
static bool equals(VType const* a, VType const* b) {
    // Make sure both objects are Integer instances.
    if (a->print != print || b->print != print)
        return false;

    // Compare the integer values.
    Integer const* intA = (Integer const*)a;
    Integer const* intB = (Integer const*)b;

    return intA->val == intB->val;
}

/**
 * Hashes the Integer object by using its contained integer value.
 * The hash value is obtained by simply returning the integer value of the Integer object.
 * Negative values will overflow to large positive values.
 * This function is specific to the Integer type and requires casting from the base VType pointer.
 * @param v A pointer to the VType object, representing an Integer.
 * @return The hash value, which is the integer value contained in the Integer object.
 */
static unsigned int hash(VType const* v) {
    // Convert the VType pointer to a more specific type.
    Integer const* this = (Integer const*)v;
    // This will overflow negative values to large positive ones.
    return this->val;
}

/**
 * Frees the memory occupied by the Integer object.
 * The Integer object is assumed to be a single block of heap memory.
 * @param v A pointer to the VType object, representing an Integer.
 */
static void destroy(VType* v) {
    // Integer is just one block of heap memory.
    free(v);
}

/**
 * Creates an Integer object on the heap, initializes its fields, and returns it as a VType pointer.
 * The Integer object represents the specified integer value and provides specific methods for Integer operations.
 * The returned VType pointer can be safely used to interact with the Integer object as a VType object.
 * @param value The integer value to be stored in the Integer object.
 * @return A pointer to the VType object, representing the created Integer.
 */
VType* makeInteger(int value) {
    // Allocate an Integer object on the heap and fill in its fields.
    Integer* this = (Integer*)malloc(sizeof(Integer));
    this->val = value;
    this->print = print;
    this->equals = equals;
    this->hash = hash;
    this->destroy = destroy;

    // Return it as a pointer to the superclass.
    return (VType*)this;
}

/**
 * Parses an integer value from the input string and creates an Integer object on the heap with the parsed value.
 * The input string is expected to be in the format of a single integer value.
 * If parsing is successful, the function returns a pointer to the VType object representing the parsed Integer.
 * If parsing fails, or the input string is not in the correct format, the function returns NULL.
 * The caller can provide an optional pointer 'n' to obtain the number of characters parsed from the input string.
 * @param init The input string to be parsed as an integer.
 * @param n A pointer to an integer where the number of characters parsed will be stored (optional).
 * @return A pointer to the VType object representing the parsed Integer, or NULL on parsing failure.
 */
VType* parseInteger(char const* init, int* n) {
    // Make sure the string is in the right format.
    int val, len;
    if (sscanf(init, "%d%n", &val, &len) != 1) {
        return NULL;
    }

    // Fill in the end pointer, if the caller asked for it.
    if (n)
        *n = len;

    // Allocate an Integer on the heap and fill in its fields.
    Integer* this = (Integer*)malloc(sizeof(Integer));
    this->val = val;
    this->print = print;
    this->equals = equals;
    this->hash = hash;
    this->destroy = destroy;

    // Return it as a pointer to the superclass.
    return (VType*)this;
}