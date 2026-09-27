# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 6 of the code (the compiler message points at it).
- **Why it fails:** The function bodies in utilities.cpp are commented out, so the LINKER reports "undefined reference to add".
- **Make the rest run:** Remove the /* */ around the functions in utilities.cpp.

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
