#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

struct Cell {
    int r, c;
};

// Returns the number of steps (or -1) and marks the path with '*' in `maze`.
int solve(std::vector<std::string>& maze)
{
    const int rows = static_cast<int>(maze.size()), cols = static_cast<int>(maze[0].size());
    Cell start{}, end{};
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c) {
            if (maze[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] == 'S') start = {r, c};
            if (maze[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] == 'E') end = {r, c};
        }

    std::vector<std::vector<Cell>> parent(static_cast<std::size_t>(rows), std::vector<Cell>(static_cast<std::size_t>(cols), Cell{-1, -1}));
    std::vector<std::vector<int>> dist(static_cast<std::size_t>(rows), std::vector<int>(static_cast<std::size_t>(cols), -1));
    auto at = [](auto& grid, Cell p) -> auto& { return grid[static_cast<std::size_t>(p.r)][static_cast<std::size_t>(p.c)]; };

    std::queue<Cell> q;
    q.push(start);
    at(dist, start) = 0;
    const int dr[]{-1, 1, 0, 0}, dc[]{0, 0, -1, 1};
    while (!q.empty()) {
        const Cell cur = q.front();
        q.pop();
        if (cur.r == end.r && cur.c == end.c) break;
        for (int d = 0; d < 4; ++d) {
            const Cell next{cur.r + dr[d], cur.c + dc[d]};
            if (next.r < 0 || next.r >= rows || next.c < 0 || next.c >= cols) continue;
            if (at(maze, next) == '#' || at(dist, next) != -1) continue;
            at(dist, next) = at(dist, cur) + 1;
            at(parent, next) = cur;
            q.push(next);
        }
    }
    if (at(dist, end) == -1) return -1;
    for (Cell p = at(parent, end); !(p.r == start.r && p.c == start.c); p = at(parent, p)) at(maze, p) = '*';
    return at(dist, end);
}

void run(std::vector<std::string> maze)
{
    const int steps = solve(maze);
    if (steps < 0) std::cout << "No path!\n";
    else std::cout << "Shortest path: " << steps << " steps\n";
    for (const auto& row : maze) std::cout << row << '\n';
    std::cout << '\n';
}

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
    run(maze);
    maze[1][8] = '#';   // block the only way into E
    run(maze);
}
