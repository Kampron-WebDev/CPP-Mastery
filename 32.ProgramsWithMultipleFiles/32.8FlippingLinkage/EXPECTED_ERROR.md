# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 20 of the code (the compiler message points at it).
- **Why it fails:** some_other_function() lives in an anonymous namespace (internal linkage), so main.cpp cannot link to it.
- **Make the rest run:** Remove the anonymous namespace in some_other_file.cpp.

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
