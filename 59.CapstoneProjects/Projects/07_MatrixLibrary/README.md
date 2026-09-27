# Project 07: Matrix Library ⭐⭐⭐

A reusable, tested, header-only `Matrix<T>` library, built with CMake.

## Spec
- `template <Arithmetic T> class Matrix` (a concept, Lesson 25) storing data in one `std::vector<T>` (row-major, cache-friendly).
- Construction: rows × cols, from nested initializer lists (`Matrix<int> m{{1,2},{3,4}}`), `identity(n)`.
- Access: `m(r, c)` with bounds checking in debug builds (`assert`).
- Operators: `+ - *` (matrix and scalar), `==`, `<<`, transpose, determinant (recursive or LU), inverse (throws if singular).
- Rule of Zero (the vector does the memory work) and move-friendly.
- **Tests** for every operation, run by CTest (Lesson 56). Mismatched dimensions throw `std::invalid_argument`.

## Milestones
1. Storage, access, printing. 2. `+ - ==` and tests. 3. Multiplication (then measure: try the i-k-j loop order and see the cache effect from Lesson 58!). 4. Transpose, determinant, inverse. 5. CMake project with library + tests + an example app.

## Stretch
- Expression templates to avoid temporaries. Parallel multiplication for big matrices.

Starter: [main.cpp](main.cpp)
