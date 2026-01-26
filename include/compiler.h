#ifndef COMPILER_H
#define COMPILER_H

#if defined(__clang__)
#elif defined(__GNUC__)
#else
#error "Unsupported compiler"
#endif

#endif // COMPILER_H
