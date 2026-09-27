# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 13 of the code (the compiler message points at it).
- **Why it fails:** add(5, 8) returns an int, which doesn't satisfy std::floating_point.
- **Make the rest run:** Change it to std::integral auto, or comment the line out.

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
