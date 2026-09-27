# Lesson 50: Files and Streams ⭐ NEW

> **In one sentence:** Programs forget everything when they close. **Files** let them remember,
> and C++ reads/writes files with the same `<<` and `>>` you already use for the console.

This lesson was **added** to the course: almost every real program saves settings, logs, or data.

---

## 🎯 You will learn

- Writing files with `std::ofstream`, reading with `std::ifstream`, both with `std::fstream`.
- Open modes: overwrite, append, binary.
- Checking for errors (file missing, no permission).
- Reading line by line and parsing CSV data.
- `std::stringstream` for parsing and building text.
- Binary files.
- `std::filesystem`: paths, folders, sizes, listing directories.

---

## 🧸 The Big Idea: a notebook vs your memory

Variables live in **RAM**, which is like remembering something in your head: gone when you sleep (the program ends).
A **file** is like writing it in a **notebook**: still there tomorrow.

```
  program ──<<──► std::ofstream ──► notes.txt   (write: "out" to the file)
  program ◄──>>── std::ifstream ◄── notes.txt   (read: "in" from the file)
```
The great news: `std::cout` is a stream, and so is a file. Everything you know about `<<`, `>>`, `std::getline`,
`std::setw` works on files too.

---

## 📚 Step by step

### 1. Writing ([Examples/01_WriteAndRead](Examples/01_WriteAndRead/main.cpp))
```cpp
#include <fstream>
std::ofstream out{"scores.txt"};              // creates (or OVERWRITES) the file
if (!out) { std::cerr << "Cannot open file\n"; return 1; }   // ALWAYS check
out << "Ama 90\n" << "Kofi 75\n";
// no close() needed: the destructor closes it (RAII, Lesson 52)
```

### 2. Reading
```cpp
std::ifstream in{"scores.txt"};
std::string name;
int score{};
while (in >> name >> score) {                 // loop stops at end of file OR bad data
    std::cout << name << " scored " << score << '\n';
}
// or line by line:
for (std::string line; std::getline(in, line);) { ... }
```

### 3. Open modes
| Mode | Meaning |
|------|---------|
| `std::ios::out` (default for ofstream) | write, **erase** old contents |
| `std::ios::app` | **append** to the end |
| `std::ios::in` (default for ifstream) | read |
| `std::ios::binary` | raw bytes, no newline translation |
```cpp
std::ofstream log{"app.log", std::ios::app};   // keep old lines, add new ones
```

### 4. Parsing text with `std::stringstream` ([Examples/02_CsvParsing](Examples/02_CsvParsing/main.cpp))
CSV = "comma-separated values", the simplest spreadsheet format:
```cpp
std::getline(in, line);                  // "Ama,19,88.5"
std::istringstream fields{line};
std::getline(fields, name, ',');         // read up to the comma
std::getline(fields, ageText, ',');
std::getline(fields, scoreText);
```
`std::ostringstream` builds strings with `<<` (like writing to a string instead of the screen).

### 5. Binary files
```cpp
std::ofstream out{"data.bin", std::ios::binary};
out.write(reinterpret_cast<const char*>(&value), sizeof(value));
```
Fast and compact, but not human-readable and not portable between machines with different layouts. Text (or JSON) is usually the better default.

### 6. `std::filesystem` ([Examples/03_Filesystem](Examples/03_Filesystem/main.cpp))
```cpp
#include <filesystem>
namespace fs = std::filesystem;
fs::path p = fs::current_path() / "data" / "scores.txt";   // / joins paths portably
fs::create_directories(p.parent_path());
fs::exists(p);  fs::file_size(p);  p.extension();  p.filename();
for (const auto& entry : fs::directory_iterator{"."}) std::cout << entry.path() << '\n';
```

---

## 🗂️ Examples

| Folder | What it shows |
|--------|---------------|
| [01_WriteAndRead](Examples/01_WriteAndRead/main.cpp) | Write, append, read back, error checks |
| [02_CsvParsing](Examples/02_CsvParsing/main.cpp) | Parse a CSV file into structs |
| [03_Filesystem](Examples/03_Filesystem/main.cpp) | Paths, folders, listing files |

Files are created in the **folder of the example** (the tasks run the program there).

## ⚠️ Common mistakes

- Not checking if the file opened (`if (!in)`) → silent empty results.
- `while (!in.eof())`, a classic bug that processes the last line twice. Loop on the read itself: `while (in >> x)` / `while (std::getline(in, line))`.
- Mixing `>>` and `getline` (the leftover newline, Lesson 03).
- Hard-coding `C:\Users\Me\...` paths. Use relative paths or `std::filesystem`.
- Windows paths in normal strings need `\\`; use `/` (works on Windows too) or raw strings `R"(...)"`.

## 🧠 Senior developer notes

- Treat all external input as **untrusted**: validate every field, handle missing/extra columns, and report the line number of bad data.
- For real data formats use libraries: JSON (nlohmann/json), CSV (rapidcsv), config (toml++). Knowing how to parse by hand makes you understand them.
- Write to a temporary file, then rename it over the old one. That's an **atomic save**: a crash can't leave a half-written file.
- Logs: append mode + a timestamp + a severity level. You'll read logs a lot in your career.

## ✅ Check yourself

1. How do you add lines to a file without erasing it?
2. Why is `while (!file.eof())` a bug?
3. How do you split `"a,b,c"` at the commas?
4. What does `fs::path{"data"} / "x.txt"` produce?

<details><summary>Answers</summary>

1. Open with `std::ios::app`.
2. `eof()` only becomes true *after* a read fails, so the loop body runs once more with stale data.
3. `std::istringstream` + `std::getline(stream, part, ',')` in a loop.
4. The path `data/x.txt` (with the right separator for the OS).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 51: Modern C++ Utilities](../51.ModernCppUtilities/README.md)
