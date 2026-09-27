# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 19 of the code (the compiler message points at it).
- **Why it fails:** Some explicit template arguments make impossible conversions (e.g. std::string to double).
- **Make the rest run:** Comment out the lines the compiler points at.

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
