#ifndef ARRAY_TOOLS_H
#define ARRAY_TOOLS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// structs
typedef struct DynamicArray {
    void *values;
    int capacity; // number of elements
    int size; // number of elements
    size_t element_size;
} DynamicArray;

extern const DynamicArray DEFAULT_ARRAY_CONFIG;

// functions
void array_resize(DynamicArray *a, int new_size);
void array_initialize(DynamicArray *a, size_t element_size, int capacity, void *initial_values, int num_of_elements);
void array_append(DynamicArray *a, void *value_ptr);
void array_insert_at(DynamicArray *a, void *value_ptr, int index);
void array_remove_at(DynamicArray *a, int index, bool lower_capacity);
void array_clear(DynamicArray *a);
void array_fill(DynamicArray *a, void *value_ptr, int slots); // to implement
bool array_includes(DynamicArray *a, void *value_ptr); // to implement
int array_find(DynamicArray *a, void *value_ptr); // to implement


void array_print_int(void *ptr);
void array_print_char(void *ptr);
void array_print_float(void *ptr);
void array_print(DynamicArray *a, void (*print_element)(void *));


#endif
