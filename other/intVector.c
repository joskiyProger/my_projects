#include <stdio.h>
#include <stdlib.h>
#include "intVector.h"
#include <string.h>


void display(IntVector* v) {
    printf("cap: %zu\n", v->capacity);
    printf("size: %zu\nvalues: ", v->size);
    for (int i = 0; i<v->capacity; i++) {
        printf("%d ", v->IntVector[i]);
    }
    printf("\n");
}

static void fill_arr_zero(IntVector * v, int start) {
    for (int i = start; i < v->capacity; i++) {
        v->IntVector[i] = 0;
    }
}

IntVector *int_vector_new(size_t initial_capacity) {
    static IntVector v;
    v.IntVector = malloc(initial_capacity);
    if (v.IntVector == NULL) {
        return NULL;
    } else {
        fill_arr_zero(&v, 0);
        v.capacity = initial_capacity;
        v.size = 0;
        return &v;
    }
} 

IntVector *int_vector_copy(const IntVector *v) {
    if (v != NULL) {
        static IntVector v2;
        v2.IntVector = malloc(v->capacity*sizeof(int));
        memcpy(v2.IntVector, v->IntVector, v->capacity);
        v2.capacity = v->capacity;
        v2.size = v->size;
        return &v2;
    } else {
        return NULL;
    }
}

void int_vector_free(IntVector *v) {
    free(v->IntVector);
}

int int_vector_get_item(const IntVector *v, size_t index) {
    return v->IntVector[index];
}

void int_vector_set_item(IntVector *v, size_t index, int item) {
    if (v->IntVector != NULL) {
        if (index < v->capacity) {
            if (index > v->size) {
                v->size = index+1;
            }
            if (index == 0) {
                v->size = 1;
            }
            v->IntVector[index] = item;
        }
    }
}

size_t int_vector_get_size(const IntVector *v) {
    return v->size;
}
size_t int_vector_get_capacity(const IntVector *v) {
    return v->capacity;
}

int int_vector_push_back(IntVector *v, int item) {
    if (v->size < v->capacity) {
        v->IntVector[v->size] = item;
    } else {
        v->capacity *= 2;
        v->IntVector = realloc(v->IntVector, v->capacity);
        
        
        fill_arr_zero(v, v->capacity/2);
        v->IntVector[v->size] = item;
    }
    v->size++;
    return 0;
}

void int_vector_pop_back(IntVector *v) {
    if (v->size > 0) {
        v->size--;
    }  
    v->IntVector[v->size] = 0;
}

int int_vector_shrink_to_fit(IntVector *v) {
    if (v->capacity >= v->size) {
        v->capacity = v->size;
        return 0;
    } else {
        return -1;
    }
}

int int_vector_resize(IntVector *v, size_t new_size) {
    if (v->size < new_size) {
        if (v->capacity < new_size) {
            v->IntVector = realloc(v->IntVector, new_size);
            v->capacity = new_size;
        }
        fill_arr_zero(v, v->size);
        v->size = new_size;
        return 0;
    } else if (v->size == new_size) {
        return 0;
    } else {
        int_vector_shrink_to_fit(v);
        return 0;
    }
    
}

int int_vector_reserve(IntVector *v, size_t new_capacity) {
    if (v->capacity < new_capacity) {
        v->IntVector = realloc(v->IntVector, new_capacity);
        v->capacity = new_capacity;
        fill_arr_zero(v, v->size);
        return 0;
    }
    return -1;
}