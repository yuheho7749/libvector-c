#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <xvector.h>
// #include <vector.h>

int main(void) {
    vector_t vec;
    int status;
    int64_t* value;

    printf("=== c vector test ===\n");

    // Initialize vector for int64_t
    status = vector_init(&vec, sizeof(int64_t), 5);
    if (status != 0) {
        printf("vector_init failed: %d\n", status);
        return status;
    }

    // Append some integers
    for (int64_t i = 0; i < 8; i++) {
        status = vector_prepend(&vec, &i);
        if (status < 0) {
            printf("%d", errno);
            fprintf(stderr, "vector_append failed at %ld: %d\n", i, status);
            goto exit;
        }
        printf("Appended %ld\n", i);
    }

    // Retrieve and print values
    printf("Vector contents:\n");
    for (size_t i = 0; i < vec.size; i++) {
        value = (int64_t *)vector_get(&vec, i);
        printf("[%zu] = %ld\n", i, *value);
        printf("elem %p\n", value);
    }

    for (int64_t i = 8; i < 13; i++) {
        status = vector_append(&vec, &i);
        if (status < 0) {
            fprintf(stderr, "vector_append failed at %ld: %d\n", i, status);
            goto exit;
        }
        printf("Appended %ld\n", i);
    }

    printf("Vector contents:\n");
    for (size_t i = 0; i < vec.size; i++) {
        value = (int64_t *)vector_get(&vec, i);
        printf("[%zu] = %ld\n", i, *value);
        printf("elem %p\n", &value);
    }

    status = 0;
exit:
    vector_free(&vec);
    printf("Vector memory freed.\n");

    return status;
}
