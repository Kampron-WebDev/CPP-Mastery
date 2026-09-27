# Project 05: Text Adventure Game ⭐⭐

A classic "go north / take key / open door" game. It's great for practising design.

## Spec
- The world is a **graph** of rooms (Lesson 54): each room has a description, items, and exits (`north → Hall`).
- Load the world from a **data file** (`world.txt`) so you can make new adventures without recompiling.
- Commands: `look`, `go <dir>`, `take <item>`, `drop <item>`, `inventory`, `use <item>`, `quit`.
- Locked doors that need an item; a win condition; a move counter.
- Command parsing is forgiving: `GO NORTH`, `n`, `go n` all work.

## Design hints
- `std::unordered_map<std::string, Room>` for rooms; `std::map<std::string, std::string>` for exits.
- Commands as a map of name → `std::function` (Lesson 42), or the Command pattern (Lesson 57).
- Keep game **logic** separate from **text I/O**: then you can test it.

## Stretch
- Save/load a game. NPCs with simple dialogue. A map printout using BFS distances.

Starter: [main.cpp](main.cpp)
