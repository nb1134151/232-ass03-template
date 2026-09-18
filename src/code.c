char * AUTHOR_NAME = (char *) "Nick Badovinac";
char * AUTHOR_AUTHORSHIP = (char *) "I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. Any collaboration or use of external resources has been properly cited. I am fully aware of the consequences of academic dishonesty and agree to abide by the university's academic integrity policy. I understand the seriousness and implications of plagiarism.";

#include <stddef.h>
#include <stdio.h>

// ============================================================
// Node — self-referential struct
// ============================================================

typedef struct Node {
    int value;
    struct Node *nextPtr;
} Node;

// ============================================================
// Function declarations
// ============================================================

void  swap(int *aPtr, int *bPtr);
char* find_last_char(char *sPtr);
void  link_three(Node *aPtr, Node *bPtr, Node *cPtr);
void  remove_middle(Node *aPtr, Node *bPtr, Node *cPtr);
void  remove_last(Node *bPtr);
void  remove_first(Node *aPtr);
void  swap_ptrs(int **aPtrPtr, int **bPtrPtr);
void  nullify(int **ppPtr);
void  assign_bytes(long long *nPtr);
int   sum_chain(Node *headPtr);


// ============================================================
//  PART 1 — IMPLEMENTATIONS 
//  Implement every function below.
//  Do NOT modify function signatures.
// ============================================================


// ============================================================
// swap
//
// Swap the VALUES stored at two integer addresses.
// Both parameters must be valid non-NULL pointers.
//
// Example:
//   int a = 5, b = 3;
//   swap(&a, &b);
//   // a == 3,  b == 5
//
// HINT:
//   You need one temporary variable.
//   Use the dereference operator to reach the values.
// ============================================================

void swap(int *aPtr, int *bPtr)
{
    int temp = 0;
      
    temp = *aPtr;
    *aPtr = *bPtr;
    *bPtr = temp;
}


// ============================================================
// find_last_char
//
// Walk the string using pointer arithmetic.
// Return a pointer to the LAST character before '\0'.
// Return NULL if the string is empty (*sPtr == '\0').
//
// Example:
//   char str[] = "hello";
//   char *resultPtr = find_last_char(str);
//   // *resultPtr == 'o'
//   // resultPtr  == str + 4
//
// HINT:
//   Check *(sPtr + 1) to know when to stop.
//   Do NOT use array indexing [ ].
// ============================================================

char* find_last_char(char *sPtr)
{
    if (*sPtr == '\0') {
        return NULL;
    }
    
    while (*sPtr != '\0'){
        
        if (*(sPtr + 1) == '\0') {
            return sPtr;
        }
        sPtr++;
        
    }
}


// ============================================================
// link_three
//
// Connect three existing nodes into a chain:
//   aPtr -> bPtr -> cPtr -> NULL
//
// All three nodes already exist — do NOT allocate anything.
//
// HINT:
//   Three assignments using the arrow operator.
// ============================================================

void link_three(Node *aPtr, Node *bPtr, Node *cPtr)
{
    aPtr->nextPtr = bPtr;
    bPtr->nextPtr = cPtr;
    cPtr->nextPtr = NULL;
}


// ============================================================
// remove_middle
//
// Given the chain:  aPtr -> bPtr -> cPtr -> NULL
// Reconnect it as:  aPtr -> cPtr -> NULL
// Disconnect bPtr:  bPtr -> NULL
//
// HINT:
//   Two assignments needed.
// ============================================================

void remove_middle(Node *aPtr, Node *bPtr, Node *cPtr)
{
    aPtr->nextPtr = cPtr;
    bPtr->nextPtr = NULL;
}


// ============================================================
// remove_last
//
// Given a chain where bPtr is the second-to-last node:
//   ... -> bPtr -> cPtr -> NULL
// Make bPtr the new last node:
//   ... -> bPtr -> NULL
//
// Only bPtr is needed.
// ============================================================

void remove_last(Node *bPtr)
{
    bPtr->nextPtr = NULL;
}


// ============================================================
// remove_first
//
// Given the chain:  aPtr -> bPtr -> cPtr -> NULL
// Isolate aPtr:     aPtr -> NULL
// Leave the rest:   bPtr -> cPtr -> NULL  (unchanged)
//
// Only aPtr is needed.
// ============================================================

void remove_first(Node *aPtr)
{
    aPtr->nextPtr = NULL;
}


// ============================================================
// swap_ptrs
//
// Swap two POINTERS — not the values they point to.
// After the call each pointer points to the other's target.
// The values at the original addresses must NOT change.
//
// Example:
//   int x = 10, y = 20;
//   int *pPtr = &x, *qPtr = &y;
//   swap_ptrs(&pPtr, &qPtr);
//   // pPtr points to y  (*pPtr == 20)
//   // qPtr points to x  (*qPtr == 10)
//   // x == 10 and y == 20 — unchanged
//
// HINT:
//   The temporary variable type is int*.
// ============================================================

void swap_ptrs(int **aPtrPtr, int **bPtrPtr)
{
    int* temp = *bPtrPtr;
    *bPtrPtr = *aPtrPtr;
    *aPtrPtr = temp;

}


// ============================================================
// nullify
//
// Set the pointer that ppPtr points to — to NULL.
// The value at the original address must NOT change.
//
// Example:
//   int x = 5;
//   int *pPtr = &x;
//   nullify(&pPtr);
//   // pPtr == NULL
//   // x    == 5  (unchanged)
//
// IMPORTANT:
//   If you only received int *pPtr and wrote pPtr = NULL,
//   the caller's pointer would be unchanged.
//   That is WHY this function receives int **ppPtr.
// ============================================================

void nullify(int **ppPtr)
{
    *ppPtr = NULL;

}


// ============================================================
// assign_bytes
//
// A long long occupies exactly 8 bytes.
// Assign values 1, 2, 3, 4, 5, 6, 7, 8 to bytes 0..7
// using a cast pointer — one byte at a time.
//
// Example:
//   long long n = 0;
//   assign_bytes(&n);
//   // byte 0 == 1
//   // byte 1 == 2
//   // ...
//   // byte 7 == 8
//
// HINT:
//   Cast nPtr to unsigned char*.
//   p[i] is identical to *(p + i).
//   Each step moves exactly 1 byte because the type is char.
// ============================================================

void assign_bytes(long long *nPtr)
{
    unsigned char *p = (unsigned char*)nPtr;
    *(p + 0) = 1;
    *(p + 1) = 2;
    *(p + 2) = 3;
    *(p + 3) = 4;
    *(p + 4) = 5;
    *(p + 5) = 6;
    *(p + 6) = 7;
    *(p + 7) = 8;


    
}


// ============================================================
// sum_chain
//
// Traverse the chain starting at headPtr.
// Return the sum of all value fields.
// Return 0 if headPtr is NULL.
//
// Example:
//   a(1) -> b(2) -> c(3) -> NULL
//   sum_chain(&a) == 6
//
// HINT:
//   Node *currentPtr = headPtr;
//   while (currentPtr != NULL) { ... }
// ============================================================

int sum_chain(Node *headPtr)
{
    if (headPtr == NULL) {
        return 0;
    }

    int sum = 0;
    while (headPtr != NULL) {
        sum = sum + headPtr->value;
        headPtr = headPtr->nextPtr;
    }
    return sum;
    
}