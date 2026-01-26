#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <vector.h>

int vector_init(vector_t *vec, size_t datatype_bytes, size_t init_capacity)
{
    if (init_capacity <= 0)
        init_capacity = 1;

    vec->data = malloc(datatype_bytes * init_capacity);
    if (!vec->data) {
        errno = ENOMEM;
        return -1;
    }

    vec->size = 0;
    vec->capacity = init_capacity;
    vec->datatype_bytes = datatype_bytes;

    return 0;
}

void vector_free(vector_t *const vec)
{
    free(vec->data);
}

static int _vector_resize(vector_t *vec, size_t new_capacity, float grow_factor)
{
    void *new_data;
    if (!vec) {
        errno = EINVAL;
        return -1;
    }

    if (grow_factor != 0) {
        new_capacity = (size_t) (vec->capacity * grow_factor + 1);
    }

    if (new_capacity <= vec->capacity) {
        errno = ECANCELED;
        return -1;
    }

    new_data = malloc(vec->datatype_bytes * new_capacity);
    if (!new_data) {
        errno = ENOMEM;
        return -1;
    }

    memcpy(new_data, vec->data, vec->size * vec->datatype_bytes);
    free(vec->data);
    vec->data = new_data;
    vec->capacity = new_capacity;
    return 0;
}

int vector_append(vector_t *vec, const void *elem)
{
    int new_size;
    if (!vec) {
        errno = EINVAL;
        return -1;
    }

    if (!elem) {
        errno = EINVAL;
        return -1;
    }

    if (vec->size > vec->capacity) {
        errno = ENOTRECOVERABLE;
        return -1;
    }

    if (vec->size + 1 > vec->capacity) {
        new_size = _vector_resize(vec, 0, VECTOR_GROW_FACTOR);
        if (new_size < 0) return new_size;
    }

    void *location = (char *)vec->data + (vec->size * vec->datatype_bytes);
    memcpy(location, elem, vec->datatype_bytes);
    vec->size++;

    return 0;
}

void *vector_get(const vector_t *vec, size_t index)
{
    if (!vec) {
        errno = EINVAL;
        return NULL;
    }

    if (index >= vec->size) {
        errno = EINVAL;
        return NULL;
    }

    return (char *)vec->data + (vec->datatype_bytes * index);
}

int vector_resize(vector_t *vec, size_t new_size)
{
    return _vector_resize(vec, new_size, 0);
}

// NOTE: sum is probably easy enough for the compiler to auto-vectorize
__attribute__((target_clones("default", "sse", "avx")))
int vector_sum_int32(const vector_t *vec, void *result)
{
    return -42;
}
