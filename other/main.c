#include <stdio.h>
#include <stdlib.h>
#include "intVector.h"

int main()
{
    IntVector *v = int_vector_new(4);
    // IntVector* v2 = int_vector_copy(v);
    // int_vector_set_item(v, 2, 1);
    display(v);
    // printf("size: %zu\n",int_vector_get_size(v));
    // printf("cap: %zu\n", int_vector_get_capacity(v));
    // printf("push_back: %d\n", int_vector_push_back(v, 5));
    
    // int_vector_pop_back(v);
    // printf("to_fit: %d\n", int_vector_shrink_to_fit(v));
    // printf("resize: %d\n", int_vector_resize(v, 5));
    // printf("reserve: %d\n", int_vector_reserve(v, 5));
    // display(v);
    
    // printf("item: %d\n",int_vector_get_item(v, 3));
    // display(v2);
    // int_vector_free(v2);
    int_vector_free(v);
}