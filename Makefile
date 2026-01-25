CC = clang

BUILD_FLAGS = -Wall -O2

# TODO: Consider building with SIMD vectorization (SSE, AVX, etc)
# BUILD_FLAGS = -Wall -O2 -march=native

LINK_FLAGS = -Iinclude -Llib -lvector

.PHONY: all lib test clean

all: lib

lib:
	$(CC) $(BUILD_FLAGS) -c src/vector.c -Iinclude -o build/vector.o
	ar rcs lib/libvector.a build/vector.o

test:
	$(CC) test/test.c $(LINK_FLAGS) -o test/test

clean:
	rm -f build/*.o test/test lib/libvector.a
