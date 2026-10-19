#include "array_tools.h"


const DynamicArray DEFAULT_ARRAY_CONFIG = {
    .capacity = 1,
    .values = (int[]){1},
    .size = 1,
    .element_size = sizeof(int)
};

/*
 * @ brief - initialize DynamicArray struct
 * @ param element_size - size of each element in the array
 * @ param *a - DynamicArray struct to initialize
 * @ param capacity - max number of elements it should hold
 * @ param initial_values[] - initial values
 * @ param num_of_elements - number of initial values
 */
void array_initialize(DynamicArray *a, size_t element_size, int capacity, void *initial_values, int num_of_elements) {
    a -> capacity = capacity;
    a -> size = num_of_elements;
    a -> element_size = element_size;
    a -> values = calloc(capacity, element_size);

    memcpy(a -> values, initial_values, num_of_elements * element_size);
}

/*
 * @ brief - resize DynamicArray capacity to specific amount
 * @ param *a - the DynamicArray struct to resize
 * @ param new_size - how many elements the new DynamicArray should hold
 */
void array_resize(DynamicArray *a, int new_size) {
    int *temp = realloc(a->values, new_size * a -> element_size);
    if (temp == nullptr) {
        puts("Failed to realloc memory");
        return;
    }

    a->values = temp;
    a->capacity = new_size;
}

/*
 * @ brief - append to the end of DynamicArray struct values
 * @ param *a - the DynamicArray struct to append to
 * @ param *value_ptr - value to append
 */
void array_append(DynamicArray *a, void *value_ptr) {
    if (a -> size == a -> capacity) {
        array_resize(a, a -> capacity + 1);
    }

    // cast char because it moves from byte to byte
    char *target = (char *)a -> values + (a -> size * a -> element_size);
    memcpy(target, value_ptr, a -> element_size);
    a -> size++;
}

/*
 * @ brief - insert new value in DynamicArray struct at index and pushes old value to right
 * @ param *a - DynamicArray struct being used
 * @ param value_ptr - value to insert
 * @ param index - index to insert at
 */
void array_insert_at(DynamicArray *a, void *value_ptr, int index) {
    if (index > a -> capacity) {
        printf("Cannot insert at index %d in %p due to indexing error!\n", index, a);
        return;
    }

    if (a -> size == a -> capacity) {
        array_resize(a, a -> capacity + 1);
    }
    a -> size++;

    char *base = a -> values;
    char *source = base + (index * a -> element_size);
    char *dest = source + a -> element_size;
    size_t bytes_to_move = (a -> size - 1 - index) * a -> element_size;

    // shift right 1
    memmove(dest, source, bytes_to_move);

    // place value
    memcpy(source, value_ptr, a -> element_size);
}

/*
 * @ brief - remove value in DynamicArray struct at certain index and shift latter values left
 * @ param *a - DynamicArray struct to remove value at
 * @ param index - index to remove value at
 * @ param lower_capacity - should this action lower the DynamicArray's capacity?
 */
void array_remove_at(DynamicArray *a, int index, bool lower_capacity) {
    if (index > a -> capacity) {
        printf("Cannot remove at index %d in %p due to indexing error!\n", index, a);
        return;
    }

    char *base = a -> values;
    char *dest = base + (index  * a -> element_size);
    char *source = dest + a -> element_size;
    size_t bytes_to_move = (a -> size - 1 - index) * a -> element_size;

    memmove(dest, source, bytes_to_move);
    a -> size--;

    if (lower_capacity) {
        array_resize(a, a -> capacity - 1);
    }
}

/*
 * @ brief - clears all values in DynamicArray struct and
 *
 */
void array_clear(DynamicArray *a) {
    free(a -> values);
    a -> values = nullptr;
};

// CALLBACK PRINT FUNCTIONS FOR ARRAY_PRINT()
// CREATE MORE IF NEED BE IN OTHER FILES

void array_print_int(void *ptr) {
    printf("%d ", *(const int *)ptr);
}

void array_print_float(void *ptr) {
    printf("%f ", *(const float *)ptr);
}

void array_print_char(void *ptr) {
    printf("%c", *(const int *)ptr);
}

/*
 * @ brief - print values in array using a callback. some callbacks defined above, others must be defined elsewhere
 * @ param *a - DynamicArray struct to for values to print out
 * @ param *print_element - callback function to help printing
 */
void array_print(DynamicArray *a, void (*print_element)(void *)) {
    if (a -> values == nullptr) {
        printf("Cannot print DynamicArray's values at %p because they are null.", &a);
        return;
    }

    char *base = a -> values;

    for (int i = 0; i < a -> size; i++) {
        char *current_element = base + (i * a -> element_size);
        print_element(current_element);
    }
    putchar('\n');
}