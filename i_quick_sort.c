/*
    Karl Toby Rosenberg
    Iterative Quick Sort Test, Minimal Stack Depth
    Inspired by Professor Siegel's algorithms course
*/

#include "i_quick_sort.h"

int main(int argc, char** argv)
{   
    printf("%s%s\n\n", "--------Iterative Quick Sort Comparison--------\n", "process smaller partition first/process larger partition second");
    
    int64_t size = 0;
    char print_on = 1;
    
    if(argc > 1)
    {
        size = atol(argv[1]);
        
        if(size == 0 && argc == 3)
        {
            size = atol(argv[2]);
            print_on = 0;
            
            if(size < 0)
            {
                printf("%" PRId64 " is an invalid array size\n", size);
                return -1;
            }
            else if(size > 10000000)
            {
                printf("%" PRId64 " may be too large\n", size);
            }
        }
        else if(size < 0)
        {
            printf("%" PRId64 " is an invalid array size\n", size);
            return -1;
        }
        else if(size > 10000000)
        {
            printf("%" PRId64 " may be too large\n", size);
        }
    }
    else
    {
        size = 50;
    }
    
    int64_t* x = (int64_t*)malloc(sizeof(int64_t)*size);
    int64_t* x_2 = (int64_t*)malloc(sizeof(int64_t)*size);
    if(!x || !x_2)return -1;
    
    srandom(time(NULL));
    int i = 0;
    for(; i < size; ++i)
    {
        x[i] = random() % 9999;
        x_2[i] = x[i];
    }
    
    if(print_on)
    {
        printf("%s", "BEFORE:\n\n");
        print_array(0, size-1, x);
        quick_sort_iterative(0, size-1, x, 1);
        printf("%s", "\nFINISHED:\n\n");
        print_array(0, size-1, x);
    }
    else
    {
        quick_sort_iterative(0, size-1, x, 0);
    }
    
    if(is_sorted(0, size-1, x)) printf("%s", "sort 1 successful\n\n");
    else printf("%s", "sort 1 unsuccessful\n\n");
    
    free(x);

    /////processes larger partitions first, results in deeper stack
    quick_sort_iterative_deeper_stack(0, size-1, x_2, print_on);

    if(is_sorted(0, size-1, x_2)) printf("%s", "sort 2 successful\n\n");
    else printf("%s", "sort 2 unsuccessful\n\n");
    
    free(x_2);

    return 0;
}

void swap(int64_t a, int64_t b, int64_t A[])
{
    int64_t temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

int quick_sort_iterative(int64_t lower, int64_t upper, int64_t A[], char stack_display)
{   
    range_t* stack = NULL;
    
    if(lower >= upper) return -1;
    
    push(lower, upper, &stack);
    
    while(stack)
    {   
        if(stack_display)print_stack(stack);
        
        range_t* curr_range = NULL;
        int64_t pivot = 0, l_marker = 0, r_marker = 0;

        if((curr_range = pop(&stack)))
        {
            int64_t lower = curr_range->lower;
            int64_t upper = curr_range->upper;
            free(curr_range);

            //swap
            if(A[lower] < A[upper])
            {
                swap(lower, upper, A);
            }

            //pivot here
            pivot = A[upper];
            l_marker = lower;
            r_marker = upper;

            do
            {
                //swap
                swap(l_marker, r_marker, A);

                do
                {
                    ++l_marker;
                }
                while(A[l_marker] < pivot);

                do
                {
                    --r_marker;
                }
                while(A[r_marker] > pivot);
            }
            while(l_marker < r_marker);

            //swap
            swap(lower, r_marker, A);
            
            //process smaller partition first (by pushing smaller partition second)
            if((r_marker-1 - lower) < (upper - r_marker+1))
            { 
                if(r_marker+1 < upper)
                {
                    if(!push(r_marker+1, upper, &stack)) return -1;
                }
                if(lower < r_marker-1)
                {
                    if(!push(lower, r_marker-1, &stack)) return -1;
                }
            }
            else
            {
                if(lower < r_marker-1)
                {
                    if(!push(lower, r_marker-1, &stack)) return -1;
                }
                if(r_marker+1 < upper)
                {
                    if(!push(r_marker+1, upper, &stack)) return -1;
                }
            }
        }
        else
        {
            return -1;
        }
    }
    return 0;  
}

int quick_sort_iterative_deeper_stack(int64_t lower, int64_t upper, int64_t A[], char stack_display)
{   
    range_t* stack = NULL;
    
    if(lower >= upper) return -1;
    
    push(lower, upper, &stack);
    
    while(stack)
    {   
        if(stack_display)print_stack(stack);
        
        range_t* curr_range = NULL;
        int64_t pivot = 0, l_marker = 0, r_marker = 0, temp = 0;

        if((curr_range = pop(&stack)))
        {
            int64_t lower = curr_range->lower;
            int64_t upper = curr_range->upper;
            free(curr_range);

            //swap
            if(A[lower] < A[upper])
            {
                temp = A[lower];
                A[lower] = A[upper];
                A[upper] = temp;
            }

            //pivot here
            pivot = A[upper];
            l_marker = lower;
            r_marker = upper;

            do
            {
                //swap
                temp = A[l_marker];
                A[l_marker] = A[r_marker];
                A[r_marker] = temp;

                do
                {
                    ++l_marker;
                }
                while(A[l_marker] < pivot);

                do
                {
                    --r_marker;
                }
                while(A[r_marker] > pivot);
            }
            while(l_marker < r_marker);

            //swap
            temp = A[lower];
            A[lower] = A[r_marker];
            A[r_marker] = temp;
            
            //process larger partition first (place it second on the stack)
            if((r_marker-1 - lower) < (upper - r_marker+1))
            { 
                if(lower < r_marker-1)
                {
                    if(!push(lower, r_marker-1, &stack)) return -1;
                }
                if(r_marker+1 < upper)
                {
                    if(!push(r_marker+1, upper, &stack)) return -1;
                }
            }
            else
            {
                if(r_marker+1 < upper)
                {
                    if(!push(r_marker+1, upper, &stack)) return -1;
                }
                if(lower < r_marker-1)
                {
                    if(!push(lower, r_marker-1, &stack)) return -1;
                }
            }
        }
        else
        {
            return -1;
        }
    }
    return 0;  
}

range_t* push(int64_t lower, int64_t upper, range_t** stack)
{
    if(!stack)return NULL;
    
    range_t *new_range = (range_t*)malloc(sizeof(range_t));
    
    if(!new_range) return NULL;

    new_range->lower = lower;
    new_range->upper = upper;
    new_range->next = (*stack);
    (*stack) = new_range;
    
    return new_range;
}

range_t* pop(range_t** stack)
{
    if(!stack || !(*stack))return NULL;
    
    range_t* to_remove = *stack;
    *stack = (to_remove)->next;
    to_remove->next = NULL;
    return to_remove;
}

void print_array(int64_t lower, int64_t upper, int64_t A[])
{
    
    for(; lower <= upper; ++lower)
    {
        printf("%" PRId64 "\n", A[lower]);
    }
    printf("%s", "\n");
}

int is_sorted(int64_t lower, int64_t upper, int64_t A[])
{
    for(; lower < upper; ++lower)
    {
        if(A[lower] > A[lower+1])return 0;
    }
    return 1;
}

void print_stack(range_t* stack)
{
    while(stack)
    {   
        printf("[%" PRId64 "-%" PRId64 "]", stack->lower, stack->upper);
        stack = stack->next; 
    }
    printf("\n");
}