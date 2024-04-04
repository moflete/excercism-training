#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

typedef struct {
    char *buffer;
    int head; // First element
    int tail; // Last element
    int length;
    bool full;
} circular_buffer_t;

typedef int buffer_value_t;

circular_buffer_t* new_circular_buffer(int size);
// void circular_buffer_destroy(circular_buffer_t *self);
short write(circular_buffer_t *buffer, buffer_value_t values);
short overwrite(circular_buffer_t *buffer, buffer_value_t values);
short read(circular_buffer_t *buffer, buffer_value_t *values);

void delete_buffer(circular_buffer_t *self);
void clear_buffer(circular_buffer_t *self);


#endif
