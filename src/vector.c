#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <vector.h>

int vector_init(vector_t *const vec, size_t datatype_bytes, size_t init_size)
{
    if (init_size <= 0)
        init_size = 1;

    vec->data = malloc(datatype_bytes * init_size);
    if (!vec->data) {
        errno = ENOMEM;
        return -1;
    }

    vec->size = 0;
    vec->max_size = init_size;
    vec->datatype_bytes = datatype_bytes;

    return 0;
}

void vector_free(vector_t *const vec)
{
    free(vec->data);
}

static int _vector_resize(vector_t *const vec, size_t new_size, float grow_factor)
{
    if (!vec) {
        errno = EINVAL;
        return -1;
    }

    if (grow_factor != 0) {
        new_size = (size_t) (vec->max_size * grow_factor + 1);
    }

    if (new_size <= vec->max_size) {
        errno = ECANCELED;
        return -1;
    }

    void *new_data = malloc(vec->datatype_bytes * new_size);
    if (!new_data) {
        errno = ENOMEM;
        return -1;
    }

    memcpy(new_data, vec->data, vec->size * vec->datatype_bytes);
    free(vec->data);
    vec->data = new_data;
    return new_size;
}

int vector_append(vector_t *const vec, const void *const elem)
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

    if (vec->size > vec->max_size) {
        errno = ENOTRECOVERABLE;
        return -1;
    }

    if (vec->size + 1 > vec->max_size) {
        new_size = _vector_resize(vec, 0, VECTOR_GROW_FACTOR);
        if (new_size < 0) return new_size;
        vec->max_size = new_size;
    }

    void *location = (char *)vec->data + (vec->size * vec->datatype_bytes);
    memcpy(location, elem, vec->datatype_bytes);
    vec->size++;

    return vec->size;
}

void *vector_get(vector_t *const vec, size_t index)
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

int vector_resize(vector_t *const vec, size_t new_size)
{
    return _vector_resize(vec, new_size, 0);
}

__attribute__((target_clones("default", "sse", "avx")))
int vector_sum(vector_t *const vec, void *result)
{
    return -42; // TODO: stub
}
