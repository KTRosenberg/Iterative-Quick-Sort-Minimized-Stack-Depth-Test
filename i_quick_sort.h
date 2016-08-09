/*
    Karl Toby Rosenberg
    Iterative Quick Sort Test, Minimal Stack Depth
    Inspired by Professor Siegel's algorithms course
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

typedef struct range
{
    int64_t lower;
    int64_t upper;
    struct range* next;
}range_t;

range_t* push(int64_t lower, int64_t upper, range_t** stack);
range_t* pop(range_t** stack);
int quick_sort_iterative(int64_t lower, int64_t upper, int64_t A[], char stack_display);
int quick_sort_iterative_deeper_stack(int64_t lower, int64_t upper, int64_t A[], char stack_display);
void swap(int64_t a, int64_t b, int64_t A[]);
void print_array(int64_t lower, int64_t upper, int64_t A[]);
int is_sorted(int64_t lower, int64_t upper, int64_t A[]);
void print_stack(range_t* stack);