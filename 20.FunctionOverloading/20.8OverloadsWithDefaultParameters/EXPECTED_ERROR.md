# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 11 of the code (the compiler message points at it).
- **Why it fails:** Two overloads can both be called with no arguments, so the call is ambiguous.
- **Make the rest run:** Comment out the print_age() call (or one of the overloads).

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
