# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 18 of the code (the compiler message points at it).
- **Why it fails:** The constructor is explicit, so 45.9 is no longer silently converted to a Square.
- **Make the rest run:** Write compare(s1, Square{45.9}).

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
