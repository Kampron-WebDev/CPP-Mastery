// Graphs as adjacency lists. BFS = shortest path (unweighted). DFS = explore everything reachable.
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using Graph = std::vector<std::vector<int>>;   // graph[v] = list of neighbours of v

std::vector<int> shortestPath(const Graph& g, int start, int goal)
{
    std::vector<int> parent(g.size(), -1);
    std::vector<bool> seen(g.size(), false);
    std::queue<int> frontier;
    frontier.push(start);
    seen[static_cast<std::size_t>(start)] = true;

    while (!frontier.empty()) {
        const int v = frontier.front();
        frontier.pop();
        if (v == goal) break;
        for (int next : g[static_cast<std::size_t>(v)]) {
            if (!seen[static_cast<std::size_t>(next)]) {
                seen[static_cast<std::size_t>(next)] = true;
                parent[static_cast<std::size_t>(next)] = v;   // remember how we got here
                frontier.push(next);
            }
        }
    }
    if (!seen[static_cast<std::size_t>(goal)]) return {};
    std::vector<int> path;
    for (int v = goal; v != -1; v = parent[static_cast<std::size_t>(v)]) path.push_back(v);
    std::reverse(path.begin(), path.end());
    return path;
}

void dfs(const Graph& g, int v, std::vector<bool>& seen)
{
    seen[static_cast<std::size_t>(v)] = true;
    for (int next : g[static_cast<std::size_t>(v)])
        if (!seen[static_cast<std::size_t>(next)]) dfs(g, next, seen);
}

int main()
{
    const std::vector<std::string> city{"Accra", "Kumasi", "Tamale", "Cape Coast", "Ho", "Takoradi", "Bolgatanga"};
    Graph roads(city.size());
    auto connect = [&](int a, int b) {
        roads[static_cast<std::size_t>(a)].push_back(b);
        roads[static_cast<std::size_t>(b)].push_back(a);
    };
    connect(0, 1); connect(0, 3); connect(0, 4); connect(1, 2);
    connect(3, 5); connect(5, 1); connect(2, 6);

    const auto path = shortestPath(roads, 4, 6);   // Ho -> Bolgatanga
    std::cout << "Fewest hops from Ho to Bolgatanga: ";
    for (std::size_t i = 0; i < path.size(); ++i) std::cout << (i ? " -> " : "") << city[static_cast<std::size_t>(path[i])];
    std::cout << "  (" << path.size() - 1 << " hops)\n";

    std::vector<bool> seen(city.size(), false);
    dfs(roads, 0, seen);
    std::cout << "Reachable from Accra: " << std::count(seen.begin(), seen.end(), true) << " of " << city.size() << " cities\n";
}
