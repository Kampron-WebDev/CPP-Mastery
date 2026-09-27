# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 30 of the code (the compiler message points at it).
- **Why it fails:** static_assert rejects non-integral types: this is the feature being shown.
- **Make the rest run:** Comment out the call that passes doubles.

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
