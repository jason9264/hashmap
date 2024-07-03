/**
    @file integer.h
    @author CSC 230
    Header for the Integer subclass of VType
*/

#ifndef INTEGER_H
#define INTEGER_H

#include "vtype.h"

/** Subclass of VType for storing integers. */
typedef struct {
    /** Inherited from VType */
    void (*print)(struct VTypeStruct const* v);

    /** Inherited from VType */
    bool (*equals)(struct VTypeStruct const* a,
                   struct VTypeStruct const* b);

    /** Inherited from VType */
    unsigned int (*hash)(struct VTypeStruct const* b);

    /** Inherited from VType */
    void (*destroy)(struct VTypeStruct* v);

    /** Value stored by this integer. */
    int val;
} Integer;

/** Make an instance of Integer holding a value parsed from the init string.
    @param init String containing the initializaiton value as text.
    @param n Optional return for the number of characters used from init.
    @return pointer to the new VType instance.
*/
VType* parseInteger(char const* init, int* n);

#endif
