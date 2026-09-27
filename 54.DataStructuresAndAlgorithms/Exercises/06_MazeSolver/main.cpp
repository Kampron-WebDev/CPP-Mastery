// ⭐⭐⭐ Exercise 06: MazeSolver
// Find the SHORTEST path from S to E in this maze ('#' = wall, '.' = open), moving up/down/left/right.
// Print the number of steps and draw the path with '*'.
//   Use BFS: a std::queue of (row, col), a "distance" or "parent" grid, and 4 directions.
// If there's no path, say so. Then add a wall to block it and test that case too.
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> maze{
        "##########",
        "#S...#...#",
        "#.##.#.#.#",
        "#.#..#.#.#",
        "#.#.##.#.#",
        "#...#..#E#",
        "##.....#.#",
        "##########",
    };
    // TODO
    (void)maze;
}
