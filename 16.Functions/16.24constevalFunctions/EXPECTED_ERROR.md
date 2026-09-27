# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 14 of the code (the compiler message points at it).
- **Why it fails:** A consteval function must get compile-time values; some_var is a run-time variable.
- **Make the rest run:** Comment out that line, or make some_var constexpr.

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
