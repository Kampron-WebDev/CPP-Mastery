# ⚠️ This example fails to build ON PURPOSE

The instructor uses this folder to **show a compiler/linker error**. Seeing the error is the lesson!

- **Where:** around line 19 of the code (the compiler message points at it).
- **Why it fails:** A std::string_view does NOT convert implicitly to std::string.
- **Make the rest run:** Write say_my_name(std::string{name_sv}).

Try it: build once and read the error message carefully (Lesson 00, Step 4). Predict the fix, apply it, and rebuild.
