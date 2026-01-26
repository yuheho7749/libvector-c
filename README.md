# C Vectorized Vector Lib
*NOTE: This is not even close to being finished*

Vector implementation (without type unions, etc) guarantees that elems are tightly packed. Also, if you know what you are doing, then you can also manipulate multiple elements (aka raw bulk accesses)

## TODO?
- [x] ~~Better tag/better type system in vector struct (that does not compromise packed elems)~~ Current design is good enough (especially for low-level SIMD)
- [ ] Vectorized vector lib (aka SIMD vectorization with SSE, AVX2/512)
