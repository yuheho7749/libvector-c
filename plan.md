# Plan

## Basic features
- [x] Finish basic `vector.h` functions (`vector_delete`)

## Basic optimizations
- [x] Change malloc to ~~posix_memalign~~ aligned_alloc
- [ ] Test performance and optimize
    - Auto-vectorization from different compilers (optimize manually if needed)
- [x] Compile option to remove safety check in functions

## SIMD Vectorization (PLANNED)
- [ ] Hand-tuned SIMD vectorization with SSE, AVX2/512
