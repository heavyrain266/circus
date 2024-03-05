#include <stdio.h>
#include <stdlib.h>

#include "../src/circus.h"

typedef struct {
	int value;
	char message[10];
} data_t;

int main() {
	size_t size = 16 * sizeof(data_t);
	void *buffer = malloc(size);

	ring_t demo = ring_init(buffer, size, sizeof(data_t));
	if (demo == NULL) {
		printf("error initializing ring buffer!\n");

		return -1;
	}

	data_t data1 = {10, "Hello"};
	data_t data2 = {20, "World"};

	int enque = ring_enqueue(demo, &data1);
	if (enque != RING_OK) {
		printf("error enqueueing data: %d\n", enque);

		return -1;
	}

	int enque2 = ring_enqueue(demo, &data2);
	if (enque2 != RING_OK) {
		printf("error enqueueing data: %d\n", enque2);

		return -1;
	}

	data_t deque_data;
	int deque = ring_dequeue(demo, &deque_data);
	if (deque != RING_OK) {
		printf("error dequeueing data: %d\n", deque);

		return -1;
	}

	printf("dequeued data: value = %d, message = %s\n", deque_data.value, deque_data.message);

	if (is_ring_full(demo)) {
		puts("ring buffer is full\n");
	} else {
		if (ring_size(demo) == 1) {
			puts("only a single element was allocated\n");
		} else {
			printf("there are %zu elements allocated\n", ring_size(demo));
		}
	}

	ring_deinit(demo);
	free(buffer);

	return 0;
}
