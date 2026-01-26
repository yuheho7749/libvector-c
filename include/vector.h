#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stddef.h>

#if defined(__clang__)
#elif defined(__GNUC__)
#else
#error "Unsupported compiler"
#endif

#ifndef VECTOR_GROW_FACTOR
#define VECTOR_GROW_FACTOR 1.5f
#endif

typedef struct {
    size_t size;
    size_t capacity;
    size_t datatype_bytes; // Low-level type system by design
    void* data;
} vector_t;

// User handles alloc/free of the vector struct
int vector_init(vector_t *vec, size_t datatype_bytes, size_t init_capacity);
void vector_free(vector_t *vec);
int vector_recast_datatype(vector_t *vec, size_t new_datatype_bytes); // TODO:

int vector_append(vector_t *vec, const void *elem);
// Useful for SIMD appends
int vector_append_custom(vector_t *vec, const void *chunk,
                         size_t chunk_size); // TODO:
int vector_prepend(vector_t *vec, const void *elem); // TODO:
int vector_insert(vector_t *vec, const void *elem, size_t index); // TODO:

void *vector_get(const vector_t *vec, size_t index);
int vector_resize(vector_t *vec, size_t new_size);

// SIMD optimized sum of vector (probably can be trivially optimized by compiler)
int vector_sum_int32(const vector_t *vec, void *result); // TODO:
int vector_sum_uint32(const vector_t *vec, void *result); // TODO:
int vector_sum_int64(const vector_t *vec, void *result); // TODO:
int vector_sum_uint64(const vector_t *vec, void *result); // TODO:
int vector_sum_float32(const vector_t *vec, void *result); // TODO:
int vector_sum_double64(const vector_t *vec, void *result); // TODO:

// TODO: max, min of vector (probably can be trivially optimized by compiler)
int vector_min_int32(const vector_t *vec, void *result); // TODO:
int vector_min_uint32(const vector_t *vec, void *result); // TODO:
int vector_min_int64(const vector_t *vec, void *result); // TODO:
int vector_min_uint64(const vector_t *vec, void *result); // TODO:
int vector_min_float32(const vector_t *vec, void *result); // TODO:
int vector_min_double64(const vector_t *vec, void *result); // TODO:

int vector_max_int32(const vector_t *vec, void *result); // TODO:
int vector_max_uint32(const vector_t *vec, void *result); // TODO:
int vector_max_int64(const vector_t *vec, void *result); // TODO:
int vector_max_uint64(const vector_t *vec, void *result); // TODO:
int vector_max_float32(const vector_t *vec, void *result); // TODO:
int vector_max_double64(const vector_t *vec, void *result); // TODO:

// Planned at some point: SIMD optimized vector-vector add, mult, and fmadd
// These SIMD ops will most likely require the most manual tuning

#endif // VECTOR_H
