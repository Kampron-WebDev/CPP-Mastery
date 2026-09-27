# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 29 of the code (the compiler message points at it).
- **Why it fails:** Calling non-const member functions through a pointer/reference to const. The comments say "Error: Expected".
- **Make the rest run:** Comment out the set_name calls and make print_info() const (Lesson 27.4 shows the fix).

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
