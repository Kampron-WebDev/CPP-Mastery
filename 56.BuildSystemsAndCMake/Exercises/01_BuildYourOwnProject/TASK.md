# ⭐⭐⭐ Exercise 01: Build Your Own CMake Project

Take your **StringList** (Lesson 39) or **Money** type (Lesson 34), or any class you're proud of, and turn it
into a proper CMake project **from an empty folder**:

1. Layout: `include/<name>/...h`, `src/...cpp`, `app/main.cpp`, `tests/test_....cpp`.
2. `CMakeLists.txt` with a library target, an app target and a test target registered with `add_test`.
3. Warnings enabled on your library only (`target_compile_options(... PRIVATE ...)`).
4. Build Debug and Release in two different build folders.
5. Make `ctest` pass. Then break one test on purpose and see CTest report it.
6. **Stretch:** fetch a real testing framework with `FetchContent` (e.g. doctest or Catch2) and rewrite your tests with it.

The solution is a working reference: [solution/](solution/). Try it yourself first!
