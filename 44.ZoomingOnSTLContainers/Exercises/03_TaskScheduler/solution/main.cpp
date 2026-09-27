#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Task {
    std::string name;
    int priority;
    int arrival;
};

// "a is LESS urgent than b": the priority_queue keeps the MOST urgent (the "largest") on top.
struct LessUrgent {
    bool operator()(const Task& a, const Task& b) const
    {
        if (a.priority != b.priority) return a.priority < b.priority;   // lower priority = less urgent
        return a.arrival > b.arrival;                                    // later arrival = less urgent
    }
};

int main()
{
    std::priority_queue<Task, std::vector<Task>, LessUrgent> queue;
    queue.push({"email", 1, 0});
    queue.push({"fix bug", 5, 1});
    queue.push({"deploy", 5, 2});
    queue.push({"coffee", 3, 3});
    queue.push({"meeting", 1, 4});

    while (!queue.empty()) {
        const Task& t = queue.top();
        std::cout << t.name << " (p" << t.priority << ", t" << t.arrival << ")\n";
        queue.pop();
    }
}
