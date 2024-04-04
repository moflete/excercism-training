#include "circular_buffer.h"

circular_buffer_t* new_circular_buffer(int size) {
    circular_buffer_t *self = malloc(sizeof(circular_buffer_t));
    self->buffer = calloc(size, sizeof(int)); // allocate with zeros
    //self->buffer = malloc(size * sizeof(int));
    self->head = 0;
    self->tail = 0;
    self->length = size;
    self->full = false;
    return self;
}

void delete_buffer(circular_buffer_t *self) {
    free(self->buffer);
    free(self); 
}

void clear_buffer(circular_buffer_t *self) {
    self->head = 0;
    self->tail = 0;
    self->full = 0; // Reset the full flag
}

//circular_buffer_enqueue
short write(circular_buffer_t *self, buffer_value_t data) {
    if (self->full) {
        // Buffer full
        errno = ENOBUFS;
        return EXIT_FAILURE;

    }
    self->buffer[self->head] = data;
    self->head = (self->head + 1) % self->length;
    if (self->head == self->tail) {
        self->full = 1; // Set flag when head catches up with tail
    }
    return EXIT_SUCCESS;
}

short overwrite(circular_buffer_t *self, buffer_value_t data) {
    // Comprueba si el buffer está lleno
    if (self->full) { // Checks if buffer is full
        // Buffer full! -> overwrite oldest data
        self->buffer[self->head] = data;
        self->head = (self->head + 1) % self->length;
        self->tail = (self->tail + 1) % self->length; // increment tail in order to overwrite the oldest value
        return EXIT_SUCCESS;
    }
//    return EXIT_SUCCESS;

    self->buffer[self->head] = data;
    self->head = (self->head + 1) % self->length;
    if (self->head == self->tail) {
        self->full = 1; // Set flag when head catches up with tail
    }
    return EXIT_SUCCESS;
}

// circular_buffer_dequeue
short read(circular_buffer_t *self, buffer_value_t *data) {
    if (self->head == self->tail && !self->full) { // Buffer empty!
        errno = ENODATA;
        return EXIT_FAILURE;
    }
    *data = self->buffer[self->tail];
    self->tail = (self->tail + 1) % self->length;
    self->full = 0; // Reset flag when dequeuing an element
    return EXIT_SUCCESS;    
}