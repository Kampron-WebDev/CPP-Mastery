# Project 06: MiniGrep ⭐⭐

Your own version of the famous `grep` tool: search for text in files.

```
rooster.exe [options] <pattern> <file-or-folder>...
  -i   ignore case          -n   show line numbers
  -r   search folders recursively (std::filesystem)
  -c   only print the count per file
  -E   treat pattern as a regular expression (std::regex)
```
```
> rooster.exe -n -i "todo" src
src\main.cpp:12: // TODO: handle errors
src\util.cpp:40: // todo remove this
```

## Milestones
1. One file, plain text search, print matching lines (Lesson 50).
2. Options parsing from `argv` with a usage message and exit codes (Lesson 18).
3. Many files and `-r` with `std::filesystem::recursive_directory_iterator`; skip binary files.
4. `-E` with `std::regex`; `-c`.
5. **Performance:** search a big folder; measure; process files in parallel with `std::async` (Lessons 53, 58).

## Definition of done
- [ ] Clear errors for missing files / bad options; exit code 0 = found, 1 = not found, 2 = error (like real grep).
- [ ] Tested on a folder with at least 100 files.

Starter: [main.cpp](main.cpp)
