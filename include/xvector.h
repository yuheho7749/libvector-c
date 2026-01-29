#ifndef XVECTOR_H
#define XVECTOR_H

#include "vector.h"

// Does not allow vector to grow and return error instead (not implemented yet)
int vector_bounded_append(vector_t *vec, const void *elem); // TODO:
int vector_bounded_prepend(vector_t *vec, const void *elem); // TODO:
int vector_bounded_insert(vector_t *vec, const void *elem, size_t index); // TODO:

// Useful for SIMD appends
int vector_append_custom(vector_t *vec, const void *chunk,
                         size_t chunk_size); // TODO:

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

#endif // XVECTOR_H
