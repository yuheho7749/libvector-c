# C Vector Lib (for fun)
*NOTE: This is not even close to being finished*

Vector implementation (without type unions, etc) guarantees that elems are tightly packed. Also, if you know what you are doing, then you can also manipulate multiple elements (aka raw bulk accesses)

## TODO?
- [ ] Better tag/better type system in vector struct (that does not compromise packed elems)
- [ ] SIMD vectorization (SSE, AVX2/512)
