# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 51 of the code (the compiler message points at it).
- **Why it fails:** add() is constrained to std::integral, so doubles are rejected: the concept working.
- **Make the rest run:** Comment out the calls with doubles.

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
