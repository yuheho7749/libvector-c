#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stddef.h>

#if defined(__clang__)
#elif defined(__GNUC__)
#else
#error "Unsupported compiler"
#endif

#define VECTOR_GROW_FACTOR 1.5f

typedef struct {
    size_t size;
    size_t max_size;
    size_t datatype_bytes; // TODO: Make better type system
    void* data;
} vector_t;

// User handles alloc/free of the vector struct
int vector_init(vector_t *const vec, size_t datatype_bytes, size_t init_size);
void vector_free(vector_t *const vec);

int vector_append(vector_t *const vec, const void *const elem);

void *vector_get(vector_t *const vec, size_t index);
int vector_resize(vector_t *const vec, size_t new_size);

// TODO:
int vector_sum(vector_t *const vec, void *result);

#endif // VECTOR_H
