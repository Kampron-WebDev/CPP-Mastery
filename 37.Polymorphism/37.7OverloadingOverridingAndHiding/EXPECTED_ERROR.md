# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 10 of the code (the compiler message points at it).
- **Why it fails:** Name hiding: the base-class overload is not visible through this call.
- **Make the rest run:** Comment out that call (or add a using declaration in the derived class).

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
