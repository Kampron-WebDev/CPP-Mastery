// ⭐⭐⭐ Exercise 03: TaskScheduler
// struct Task { std::string name; int priority; int arrival; };
// Process tasks in order: HIGHEST priority first; for equal priority, EARLIEST arrival first.
// Use std::priority_queue<Task, std::vector<Task>, Compare> with your own Compare functor/lambda.
// Careful: priority_queue puts the "largest" on top, so think about what "less" means!
// Tasks (name, priority, arrival):
//   ("email", 1, 0) ("fix bug", 5, 1) ("deploy", 5, 2) ("coffee", 3, 3) ("meeting", 1, 4)
// Expected order: fix bug, deploy, coffee, email, meeting
#include <iostream>
#include <queue>
#include <string>
#include <vector>

int main()
{
    // TODO
}
