# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 36 of the code (the compiler message points at it).
- **Why it fails:** std::unique_ptr is move-only: copying it is forbidden.
- **Make the rest run:** Use std::move(ptr_int) instead of copying.

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
