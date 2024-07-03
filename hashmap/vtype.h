#ifndef VTYPE_H
#define VTYPE_H

// Define your VType struct here
typedef struct VTypeStruct {
    // Members of the VType struct
    char type;
    union {
        char* text;
        int integer;
    } value;
} VType;

// Function prototypes
VType* makeText(char* value);
VType* makeInteger(int value);
void freeVType(VType* v);
void printVType(const VType* v);
_Bool equalsVType(const VType* a, const VType* b);
unsigned int hashVType(const VType* v);

#endif // VTYPE_H

