#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

// ============================================================
// Forward declarations — implemented in code.c
// ============================================================

typedef struct Node {
    int value;
    struct Node *nextPtr;
} Node;

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
//  UNIT TESTS
//
//  Rules:
//  - Set up all variables on the STACK — no malloc.
//  - Call the function under test.
//  - Use TEST_ASSERT_* to verify the result.
//  - Each function must be self-contained.
//  - Do NOT modify function names or signatures.
// ============================================================


// ============================================================
// test_swap_basic
//
// Call swap with two different integer values.
// Verify that both variables hold the exchanged values
// after the call.
// ============================================================

void test_swap_basic(void)
{
    int a = 5;
    int b = 3;
    int expected_a = 3;
    int expected_b = 5;

    swap(&a, &b);

    TEST_ASSERT_EQUAL(expected_a, a);
    TEST_ASSERT_EQUAL(expected_b, b);
}


// ============================================================
// test_swap_equal
//
// Call swap with two variables that hold the same value.
// Verify that both variables still hold that value after
// the call — nothing should change.
// ============================================================

void test_swap_equal(void)
{
    int a = 3;
    int b = 3;
    swap(&a, &b);
    TEST_ASSERT_EQUAL(a, b);
}


// ============================================================
// test_find_last_basic
//
// Call find_last_char on a string with multiple characters.
// Verify that the returned pointer points to the correct
// last character and has the correct address.
// ============================================================

void test_find_last_basic(void)
{
    char str[] = "hello";
    char expected_char = 'o';
    char null_byte = '\0';
    char *resultPtr = find_last_char(str);
    TEST_ASSERT_EQUAL(expected_char, *resultPtr);
    TEST_ASSERT_EQUAL(null_byte, *(resultPtr + 1));
    
}


// ============================================================
// test_find_last_single
//
// Call find_last_char on a string with exactly one character.
// Verify that the returned pointer points to that character
// and equals the address of the first element.
// ============================================================

void test_find_last_single(void)
{
    char str[] = "a";
    char *expected_char = "a";
    char *resultPtr = find_last_char(str);

    TEST_ASSERT_EQUAL(*expected_char, *resultPtr);

}


// ============================================================
// test_find_last_empty
//
// Call find_last_char on an empty string.
// Verify that the function returns NULL.
// ============================================================

void test_find_last_empty(void)
{
    char str[] = "";
    char *resultPtr = find_last_char(str);
    TEST_ASSERT_NULL(resultPtr);
}


// ============================================================
// test_link_three_chain
//
// Declare three Node variables on the stack.
// Call link_three to connect them.
// Verify that:
//   - aPtr->nextPtr points to bPtr
//   - bPtr->nextPtr points to cPtr
//   - cPtr->nextPtr is NULL
// ============================================================

void test_link_three_chain(void)
{
    Node aPtr;
    Node bPtr;
    Node cPtr;
    
    link_three(&aPtr, &bPtr, &cPtr);
    TEST_ASSERT_EQUAL(&bPtr, aPtr.nextPtr);
    TEST_ASSERT_EQUAL(&cPtr, bPtr.nextPtr);
    TEST_ASSERT_NULL(cPtr.nextPtr);
    
    
}


// ============================================================
// test_remove_middle_reconnects
//
// Build the chain a -> b -> c -> NULL using link_three.
// Call remove_middle.
// Verify that:
//   - aPtr->nextPtr now points directly to cPtr
//   - bPtr->nextPtr is NULL (disconnected)
// ============================================================

void test_remove_middle_reconnects(void)
{
    Node aPtr;
    Node bPtr;
    Node cPtr;
    link_three(&aPtr, &bPtr, &cPtr);
    remove_middle(&aPtr, &bPtr, &cPtr);
    TEST_ASSERT_EQUAL(&cPtr, aPtr.nextPtr);
    TEST_ASSERT_NULL(bPtr.nextPtr);
}


// ============================================================
// test_remove_last_truncates
//
// Build the chain a -> b -> c -> NULL using link_three.
// Call remove_last with bPtr.
// Verify that:
//   - bPtr->nextPtr is NULL
//   - aPtr->nextPtr still points to bPtr (unchanged)
// ============================================================

void test_remove_last_truncates(void)
{
    Node aPtr;
    Node bPtr;
    Node cPtr;
    link_three(&aPtr, &bPtr, &cPtr);
    remove_last(&bPtr);
    TEST_ASSERT_EQUAL(&bPtr, aPtr.nextPtr);
    TEST_ASSERT_NULL(bPtr.nextPtr);
}


// ============================================================
// test_remove_first_isolates
//
// Build the chain a -> b -> c -> NULL using link_three.
// Call remove_first with aPtr.
// Verify that:
//   - aPtr->nextPtr is NULL (isolated)
//   - bPtr->nextPtr still points to cPtr (unchanged)
// ============================================================

void test_remove_first_isolates(void)
{
    Node aPtr;
    Node bPtr;
    Node cPtr;
    link_three(&aPtr, &bPtr, &cPtr);
    
    remove_first(&aPtr);
    TEST_ASSERT_NULL(aPtr.nextPtr);
    TEST_ASSERT_EQUAL(&cPtr, bPtr.nextPtr);
}


// ============================================================
// test_swap_ptrs_redirects
//
// Declare two integer variables and two pointers to them.
// Call swap_ptrs.
// Verify that each pointer now points to the other variable.
// ============================================================

void test_swap_ptrs_redirects(void)
{
    int x = 10;
    int y = 20;
    int *xPtr = &x;
    int *yPtr = &y;
    swap_ptrs(&xPtr, &yPtr);
    TEST_ASSERT_EQUAL(&x, yPtr);
    TEST_ASSERT_EQUAL(&y, xPtr);

}


// ============================================================
// test_swap_ptrs_values_unchanged
//
// Declare two integer variables and two pointers to them.
// Call swap_ptrs.
// Verify that the INTEGER VALUES at the original addresses
// are completely unchanged after the call.
// ============================================================

void test_swap_ptrs_values_unchanged(void)
{
    int x = 10;
    int y = 20;
    int *xPtr = &x;
    int *yPtr = &y;
    swap_ptrs(&xPtr, &yPtr);

    TEST_ASSERT_EQUAL(20, *xPtr);
    TEST_ASSERT_EQUAL(10, *yPtr);
    
}


// ============================================================
// test_nullify_sets_null
//
// Declare an integer and a pointer to it.
// Verify the pointer is NOT NULL before the call.
// Call nullify.
// Verify the pointer IS NULL after the call.
// ============================================================

void test_nullify_sets_null(void)
{
    int x = 5;
    int *xPtr = &x;

    TEST_ASSERT_NOT_NULL(xPtr);
    nullify(&xPtr);
    TEST_ASSERT_NULL(xPtr);
}


// ============================================================
// test_nullify_value_unchanged
//
// Declare an integer and a pointer to it.
// Call nullify.
// Verify that the INTEGER VALUE at the original address
// is unchanged after the call.
// ============================================================

void test_nullify_value_unchanged(void)
{
    int x = 10;
    int *xPtr = &x;

    nullify(&xPtr);
    TEST_ASSERT_EQUAL(10, x);
}


// ============================================================
// test_assign_bytes_first_and_last
//
// Declare a long long variable initialized to zero.
// Call assign_bytes.
// Cast the address to unsigned char* and verify that
// byte 0 equals 1 and byte 7 equals 8.
// ============================================================

void test_assign_bytes_first_and_last(void)
{
    long long n = 0;
    assign_bytes(&n);
    unsigned char *p = (unsigned char*)&n;
    TEST_ASSERT_EQUAL(1, *(p+0));
    TEST_ASSERT_EQUAL(8, *(p+7));
}


// ============================================================
// test_assign_bytes_all
//
// Declare a long long variable initialized to zero.
// Call assign_bytes.
// Cast the address to unsigned char* and verify that
// every byte i contains the value i + 1.
// ============================================================

void test_assign_bytes_all(void)
{
    long long n = 0;
    assign_bytes(&n);
    unsigned char *p = (unsigned char*)&n;
    for (int i = 0; i < sizeof(n); i++) {
        TEST_ASSERT_EQUAL((i + 1), *(p + i));
    }
}


// ============================================================
// test_sum_chain_basic
//
// Declare three Node variables on the stack.
// Link them into a chain using link_three.
// Assign known values to each node.
// Call sum_chain and verify the returned sum is correct.
// ============================================================

void test_sum_chain_basic(void)
{
    Node aPtr;
    Node bPtr;
    Node cPtr;

    link_three(&aPtr, &bPtr, &cPtr);

    aPtr.value = 3;
    bPtr.value = 4;
    cPtr.value = 5;

    int sum = sum_chain(&aPtr);

    TEST_ASSERT_EQUAL(12, sum);


}


// ============================================================
// test_sum_chain_single
//
// Declare a single Node with a known value.
// Set nextPtr to NULL.
// Call sum_chain and verify it returns that single value.
// ============================================================

void test_sum_chain_single(void)
{
    Node aPtr;

    aPtr.value = 3;
    aPtr.nextPtr = NULL;
    int sum = sum_chain(&aPtr);
    TEST_ASSERT_EQUAL(3, sum);
}


// ============================================================
// test_sum_chain_null
//
// Call sum_chain with NULL.
// Verify the function returns 0 without crashing.
// ============================================================

void test_sum_chain_null(void)
{
    int sum = sum_chain(NULL);
    TEST_ASSERT_EQUAL(0, sum);
}