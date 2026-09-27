# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 6 of the code (the compiler message points at it).
- **Why it fails:** The move constructor is deleted, so moving a Point is refused.
- **Make the rest run:** Comment out that line.

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
