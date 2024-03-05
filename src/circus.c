#include <stdlib.h>
#include <string.h>

#include "./circus.h"

#define RING_IS_FULL(self) ((self->tail + 1) % self->capacity == self->head)
#define RING_IS_EMPTY(self) (self->head == self->tail)

ring_t ring_init(void *buffer, size_t size, size_t element_size) {
	if (buffer == NULL || size == 0 || element_size == 0) {
		return NULL;
	}

	ring_t self = malloc(sizeof(ringbuf_t));
	if (self == NULL) {
		return NULL;
	}

	self->buffer = buffer;
	self->element_size = element_size;
	self->capacity = size / element_size;
	self->head = 0;
	self->tail = 0;

	return self;
}

void ring_deinit(ring_t self) {
	if (self != NULL) {
		free(self);
	}
}

void ring_reset(ring_t self) {
	if (self != NULL) {
		self->head = 0;
		self->tail = 0;
	}
}

int ring_enqueue(ring_t self, const ring_data_t *data) {
	if (self == NULL || data == NULL) {
		return RING_INVALID_ARGUMENTS;
	}

	if (RING_IS_FULL(self)) {
		return RING_FULL;
	}

	// calculate destination address in buffer
	// based on tail index and element size
	char *dest = (char *)self->buffer + (self->tail * self->element_size);

	// copy the data from source (data)
	// to destination (buffer) with element size
	memcpy(dest, data, self->element_size);

	// update tail index for next element
	self->tail = (self->tail + 1) % self->capacity;

  	return RING_OK;
}

int ring_dequeue(ring_t self, ring_data_t *data) {
	if (self == NULL || data == NULL) {
		return RING_INVALID_ARGUMENTS;
	}

	if (RING_IS_EMPTY(self)) {
		return RING_EMPTY;
	}

	// calculate destination address in buffer
	// based on head index and element size
	char *src = (char *)self->buffer + (self->head * self->element_size);

	// copy the data from source (data)
	// to destination (buffer) with element size
	memcpy(data, src, self->element_size);

	// update head index for next element
	self->head = (self->head + 1) % self->capacity;

	return RING_OK;
}

int ring_peek_at(ring_t self, ring_data_t *data, unsigned int peek) {
	if (self == NULL || data == NULL) {
		return RING_INVALID_ARGUMENTS;
	}

	if (RING_IS_EMPTY(self)) {
		return RING_EMPTY;
	}

	// calculate index of the element to peek at
	size_t index = (self->head + peek) % self->capacity;

	// calculate source address in buffer
	// based on the calculated index and element size
	char *src = (char *)self->buffer + (index * self->element_size);

	// copy the data from source (buffer)
	// to destination (data) with element size
	memcpy(data, src, self->element_size);

	return RING_OK;
}

bool is_ring_full(ring_t self) {
	return RING_IS_FULL(self);
}

bool is_ring_empty(ring_t self) {
	return RING_IS_EMPTY(self);
}

size_t ring_size(ring_t self) {
	if (self->tail >= self->head) {
		return self->tail - self->head;
	} else {
		return self->capacity - (self->head - self->tail);
	}
}

size_t ring_capacity(ring_t self) {
	return self->capacity;
}
