#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <vector.h>

//
// Compile options
//

#if defined(__GNUC__)
#define no_optimize __attribute__((optimize("O0")))
#define optimize_O1 __attribute__((optimize("O1")))
#define optimize_O2 __attribute__((optimize("O2")))
#define optimize_O3 __attribute__((optimize("O3")))

#elif defined(CLANG_COMPILER)
#define no_optimize __attribute__((optnone))
#define optimize_O1
#define optimize_O2
#define optimize_O3

#else
#error "Unsupported compiler"
#endif

// Safety checks on "hot" functions (most important for append, get).
// Also turns off in prepend, insert, remove too.
#ifndef HOT_GUARDRAILS_OFF
#define HOT_GUARDRAIL
#endif

// Not recommended to turn this off b/c "cold" function are not
// expected to run that frequently.
#ifndef COLD_GUARDRAILS_OFF
#define COLD_GUARDRAIL
#endif


//
// Standard vector operations
//

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

int vector_recast_datatype(vector_t *vec, size_t new_datatype_bytes)
{
    if (new_datatype_bytes < 0 || new_datatype_bytes > vec->size) {
        errno = EINVAL;
        return -1;
    }

    vec->datatype_bytes = new_datatype_bytes;
    return 0;
}

static int _vector_resize(vector_t *vec, size_t new_capacity, float grow_factor)
{
    void *new_data;

    if (grow_factor != 0) {
        new_capacity = (size_t) (vec->capacity * grow_factor + 1);
    }

#ifdef COLD_GUARDRAIL
    if (new_capacity <= vec->capacity) {
        errno = ECANCELED;
        return -1;
    }
#endif

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

int vector_resize(vector_t *vec, size_t new_size)
{
    return _vector_resize(vec, new_size, 0);
}

int vector_append(vector_t *vec, const void *elem)
{
    size_t new_size;
    void *location;
    int retval = 0;

#ifdef HOT_GUARDRAIL
    // Might remove safety check for slightly faster implementation?
    if (vec->size > vec->capacity) {
        errno = ENOTRECOVERABLE;
        return -1;
    }
#endif

    if (vec->size + 1 > vec->capacity) {
        new_size = _vector_resize(vec, 0, VECTOR_GROW_FACTOR);
        if (new_size < 0)
            return new_size;
        retval = 1;
    }

    location = (char *)vec->data + (vec->size * vec->datatype_bytes);
    memcpy(location, elem, vec->datatype_bytes);
    vec->size++;
    return retval;
}

int vector_prepend(vector_t *vec, const void *elem)
{
    return vector_insert(vec, elem, 0);
}

int vector_insert(vector_t *vec, const void *elem, size_t index)
{
    size_t new_capacity;
    void *new_data;
    char *dest;
    char *src;
    size_t i;

#ifdef HOT_GUARDRAIL
    // Might remove safety check for slightly faster implementation?
    if (vec->size > vec->capacity) {
        errno = ENOTRECOVERABLE;
        return -1;
    }
#endif

    // Increase capacity
    if (vec->size + 1 > vec->capacity) {
        new_capacity = (size_t) (vec->capacity * VECTOR_GROW_FACTOR + 1);
        new_data = malloc(vec->datatype_bytes * new_capacity);
        if (!new_data) {
            errno = ENOMEM;
            return -1;
        }

        memcpy(new_data, vec->data, vec->datatype_bytes * index);

        dest = (char *)new_data + (vec->datatype_bytes * index);
        memcpy(dest, elem, vec->datatype_bytes);

        dest = (char *)dest + vec->datatype_bytes;
        src = (char *)vec->data + (vec->datatype_bytes * index);
        memcpy(dest, src, (vec->size - index) * vec->datatype_bytes);

        free(vec->data);
        vec->capacity = new_capacity;
        vec->data = new_data;
        vec->size++;
        return 1;
    }

    if (vec->size > 0) {
        i = vec->size * vec->datatype_bytes - 1;
        while (i >= (vec->datatype_bytes * index)) {
            ((char *)vec->data)[i + vec->datatype_bytes] = ((char *)vec->data)[i];
            if (i == 0)
                break;
            i--;
        }
    }
    dest = (char *)vec->data + (vec->datatype_bytes * index);
    memcpy(dest, elem, vec->datatype_bytes);
    vec->size++;

    return 0;
}

void *vector_get(const vector_t *vec, size_t index)
{
#ifdef HOT_GUARDRAIL
    if (index < 0 || index >= vec->size) {
        errno = EINVAL;
        return NULL;
    }
#endif

    return (char *)vec->data + (vec->datatype_bytes * index);
}

int vector_remove(vector_t *vec, size_t index)
{
    size_t i;

#ifdef HOT_GUARDRAIL
    if (vec->size > vec->capacity) {
        errno = ENOTRECOVERABLE;
        return -1;
    }

    if (index < 0 || index >= vec->size) {
        errno = EINVAL;
        return -1;
    }

    if (vec->size == 0) {
        errno = ECANCELED;
        return -1;
    }
#endif

    i = vec->datatype_bytes * index;
    while (i < vec->datatype_bytes * (vec->size - 1)) {
        ((char *)vec->data)[i] = ((char *)vec->data)[i + vec->datatype_bytes];
        i++;
    }
    vec->size--;

    return 0;
}

//
// Xtended vector operations
//

#ifdef XVECTOR_LIB
// NOTE: sum is probably easy enough for the compiler to auto-vectorize
__attribute__((target_clones("default", "sse", "avx")))
int vector_sum_int32(const vector_t *vec, void *result)
{
    return -42;
}
#endif // XVECTOR_LIB
