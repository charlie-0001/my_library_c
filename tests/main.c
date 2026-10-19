#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include  "../include/array_tools.h"


int main() {
    DynamicArray new_array = DEFAULT_ARRAY_CONFIG;
    array_initialize(&new_array, sizeof(float),4, (float[]){3, 4, 5, 6}, 4);
    array_print(&new_array, array_print_float);

    array_append(&new_array, &(float){3});
    array_print(&new_array, array_print_float);

    array_insert_at(&new_array, &(float){67}, 0);
    array_print(&new_array, array_print_float);

    array_remove_at(&new_array, 4, true);
    array_print(&new_array, array_print_float);

    array_clear(&new_array);
    array_print(&new_array, array_print_float);

    putchar('\n');
}