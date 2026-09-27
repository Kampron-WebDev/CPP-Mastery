# See the 4 build stages yourself

Open a terminal in **this folder** and run each command. Then open the file it creates.

| Stage | Command | Look at |
|-------|---------|---------|
| 1. Preprocess | `g++ -std=c++20 -E main.cpp -o main.ii` | `main.ii` is huge because `#include <iostream>` pasted ~30 000 lines in, and `GREETING` was replaced by the text |
| 2. Compile | `g++ -std=c++20 -S main.cpp -o main.s` | `main.s` is **assembly**: tiny CPU instructions like `mov`, `call` |
| 3. Assemble | `g++ -std=c++20 -c main.cpp -o main.o` | `main.o` is machine code (binary, not readable) |
| 4. Link | `g++ main.o -o rooster.exe` | `rooster.exe`: run it with `.\rooster.exe` |

**Try:** in `main.ii`, press `Ctrl+End` to jump to the bottom. Your tiny `main` is there,
after thousands of lines of library code.

Delete the generated files afterwards (`main.ii`, `main.s`, `main.o`).
