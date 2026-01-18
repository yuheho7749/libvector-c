#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stddef.h>

#define VECTOR_GROW_FACTOR 1.5f

typedef struct {
    size_t size;
    size_t max_size;
    size_t datatype_bytes;
    void* data;
} vector_t;

// *Deprecated*: vector struct alloc/free is handled automatically
int vector_create(vector_t **vec, size_t datatype_bytes, size_t init_size);
void vector_destroy(vector_t *vec);

// User alloc/free the vector struct
int vector_init(vector_t *const vec, size_t datatype_bytes, size_t init_size);
void vector_free(vector_t *const vec);

int vector_append(vector_t *const vec, const void *const elem);

// *Deprecated*: use vector get instead
void* vector_get_detail(vector_t *const vec, size_t index);
void* vector_get(vector_t *const vec, size_t index);
int vector_resize(vector_t *const vec, size_t new_size);

#endif // VECTOR_H
