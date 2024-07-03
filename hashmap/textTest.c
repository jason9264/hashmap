// Simple test program for the text component.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vtype.h"

int main() {
    // Try out the parse function for a few text objects.
    int n;

    VType* t1 = parseText("\"abc\"", &n);
    // Should have read five characters.
    assert(n == 5);

    VType* t2 = parseText(" \"abc\" ", &n);
    // Should have read six characters.
    assert(n == 6);

    // The n parameter should be optional.
    VType* t3 = parseText("\"xyz\"", NULL);

    // The first two text objects should be equal.
    assert(t1->equals(t1, t2));

    // Should also work the other way around.
    assert(t2->equals(t2, t1));

    // The third object should be different.
    assert(!t1->equals(t1, t3));
    assert(!t2->equals(t2, t3));

    // Try a longer string.
    VType* t4 = parseText("\"ABCDEFGHIJKLMNOPQRSTUVWXYZ\"", &n);
    assert(n == 28);

    // Some examples from the wikipedia page for the Jenkins hash function.
    VType* t5 = parseText("\"a\"", &n);
    assert(n == 3);

    VType* t6 = parseText("\"The quick brown fox jumps over the lazy dog\"", &n);
    assert(n == 45);

    // Check the hash values for these objects.
    assert(t1->hash(t1) == 0xED131F5B);
    assert(t2->hash(t2) == 0xED131F5B);
    assert(t3->hash(t3) == 0x418B8F9E);
    assert(t4->hash(t4) == 0x17D780E5);

    // Check against the expected hashes from the wikipedia page.
    assert(t5->hash(t5) == 0xCA2E9442);
    assert(t6->hash(t6) == 0x519E91F5);

    // Get all the Text objects to print themselves (we can't test this
    // with assert)
    t1->print(t1);
    printf("\n");
    t2->print(t2);
    printf("\n");
    t3->print(t3);
    printf("\n");
    t4->print(t4);
    printf("\n");
    t5->print(t5);
    printf("\n");
    t6->print(t6);
    printf("\n");

    // Free all the Text objects.
    t1->destroy(t1);
    t2->destroy(t2);
    t3->destroy(t3);
    t4->destroy(t4);
    t5->destroy(t5);
    t6->destroy(t6);

    return EXIT_SUCCESS;
}
