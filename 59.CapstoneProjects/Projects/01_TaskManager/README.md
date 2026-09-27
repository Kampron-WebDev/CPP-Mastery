# Project 01: Task Manager CLI ⭐⭐

A command-line to-do app that **saves your tasks to a file**, so they're still there next time.

## Features (the spec)
```
> add Buy milk | high | 2026-10-01
Added task #1
> add Finish C++ lesson 30 | medium
Added task #2
> list
 #  Done  Priority  Due         Title
 1  [ ]   HIGH      2026-10-01  Buy milk
 2  [ ]   medium    -           Finish C++ lesson 30
> done 1
> list --pending
> remove 2
> sort priority          (or: sort due, sort id)
> find milk
> stats                  (total, done, pending, % complete)
> help
> quit                   (tasks are saved automatically after every change)
```

## Milestones
1. `Task` struct/class + `enum class Priority`; `add` and `list` in memory.
2. `done`, `remove` by id (ids never get reused), with errors for unknown ids.
3. Save/load to `tasks.txt` (one task per line, fields separated by a TAB character). Survive a restart.
4. `sort`, `find`, `stats`, `list --pending`.
5. Split into files: `task.h/.cpp`, `task_store.h/.cpp` (list + persistence), `main.cpp` (commands only).

## Definition of done
- [ ] No crashes on bad input (`done abc`, `done 999`, empty title, missing fields).
- [ ] Data survives restarting the program.
- [ ] `main.cpp` contains no file I/O and no sorting logic (separation of concerns).
- [ ] Builds warning-free with `-Wall -Wextra`.

## Stretch goals
- Due-date checking with `std::chrono` (show OVERDUE).
- Undo last command (Command pattern, Lesson 57).
- Command-line mode: `rooster.exe add "Buy milk"` (Lesson 18).

Starter: [main.cpp](main.cpp) · Reference: [solution/](solution/main.cpp)
