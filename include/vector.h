// SPDX-License-Identifier: LGPL-2.1-only

/*
 * Vector (dynamic array) library
 *
 * Copyright (c) 2026 yuheho7749
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stddef.h>

// --- CLANG ---
#if defined(__clang__)
#define CLANG_COMPILER

// --- GNUC (assumes gcc flags/attributes as "standard") ---
#elif defined(__GNUC__)
#define GNUC_COMPILER

// --- Other compilers ---
#else
#error "Unsupported compiler"
#endif


#ifndef VECTOR_GROW_FACTOR
#define VECTOR_GROW_FACTOR 1.5f
#endif // Compiler check end

typedef struct {
    size_t size;
    size_t capacity;
    size_t datatype_bytes; // Low-level type system by design
    void* data;
} vector_t;

// User handles alloc/free of the vector struct (but not the data field)
int vector_init(vector_t *vec, size_t datatype_bytes, size_t init_capacity);
void vector_free(vector_t *vec);
int vector_recast_datatype(vector_t *vec, size_t new_datatype_bytes);
int vector_resize(vector_t *vec, size_t new_size);

int vector_append(vector_t *vec, const void *elem);
int vector_prepend(vector_t *vec, const void *elem);
int vector_insert(vector_t *vec, const void *elem, size_t index);
int vector_remove(vector_t *vec, size_t index);

void *vector_get(const vector_t *vec, size_t index);

#endif // VECTOR_H
