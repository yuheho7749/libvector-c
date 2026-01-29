# Vectorized Vector Library (for C)
*STATUS: Basic implementation NOT done yet!*

Vectorized (soon) vector library (aka vectorized dynamic array library) that exposes "low-level" data types (raw bytes) while not being too hard to use.

## Starter Description
This library has two header files `vector.h` and `xvector.h`.
- `vector.h`: basic vector (dynamic array) functions.
- `xvector.h`: eXtended vector operations (planned, but not implemented yet), in addition to basic `vector.h` functions.

## Timeline
- [ ] Finish basic `vector.h` functions (`vector_delete`)
- [ ] Test performance and optimize
    - Auto-vectorization from different compilers (optimize manually if needed)

### Vectorization (PLANNED)
- [ ] Hand-tuned SIMD vectorization with SSE, AVX2/512
