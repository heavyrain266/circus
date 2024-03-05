#include <stdio.h>
#include <stdlib.h>

#include "../circus.h"

typedef struct {
  int value;
  char message[10];
} data_t;

int main() {
  size_t size = 10 * sizeof(data_t);
  void *buffer = malloc(size);

  ring_t ring = ring_init(buffer, size, sizeof(data_t));
  if (ring == NULL) {
    printf("Error initializing ring buffer!\n");
    return -1;
  }

  data_t data1 = {10, "Hello"};
  data_t data2 = {20, "World"};

  int ret = ring_enqueue(ring, &data1);
  if (ret != RING_OK) {
    printf("Error enqueueing data: %d\n", ret);
    return -1;
  }

  ret = ring_enqueue(ring, &data2);
  if (ret != RING_OK) {
    printf("Error enqueueing data: %d\n", ret);
    return -1;
  }

  data_t dequeued_data;
  ret = ring_dequeue(ring, &dequeued_data);
  if (ret != RING_OK) {
    printf("Error dequeueing data: %d\n", ret);
    return -1;
  }

  printf("Dequeued data: value = %d, message = %s\n", dequeued_data.value,
         dequeued_data.message);

  if (is_ring_full(ring)) {
    printf("Ring buffer is full\n");
  } else if (is_ring_empty(ring)) {
    printf("Ring buffer is empty\n");
  } else {
    printf("Ring buffer has elements\n");
  }

  size_t current_size = ring_size(ring);
  size_t capacity = ring_capacity(ring);

  printf("Current size: %zu, Capacity: %zu\n", current_size, capacity);

  ring_deinit(ring);

  free(buffer);

  return 0;
}
