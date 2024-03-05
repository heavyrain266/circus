#ifndef CIRCUS_MALLOC_H_
#define CIRCUS_MALLOC_H_

#include <stdbool.h>
#include <stdint.h>


typedef void *ring_data_t;

typedef struct ringbuf_t {
  ring_data_t *buffer;
  size_t element_size;
  size_t capacity;
  size_t head;
  size_t tail;
} ringbuf_t;

typedef ringbuf_t *ring_t;

enum circus_error_t {
  RING_OK = 0,
  RING_FULL,
  RING_EMPTY,
  RING_INVALID_ARGUMENTS,
};

ring_t ring_init(void *buffer, size_t size, size_t element_size);

void ring_deinit(ring_t self);
void ring_reset(ring_t self);

int ring_enqueue(ring_t self, const ring_data_t *data);
int ring_dequeue(ring_t self, ring_data_t *data);
int ring_peek(ring_t self, ring_data_t *data, unsigned int peek);

bool is_ring_full(ring_t self);
bool is_ring_empty(ring_t self);

size_t ring_size(ring_t self);
size_t ring_capacity(ring_t self);

#endif // CIRCUS_MALLOC_H_
