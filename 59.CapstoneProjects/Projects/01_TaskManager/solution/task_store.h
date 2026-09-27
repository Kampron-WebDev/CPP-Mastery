#pragma once
#include <string>
#include <vector>

#include "task.h"

// Owns the tasks and their persistence. Knows nothing about the command line.
class TaskStore {
public:
    explicit TaskStore(std::string filePath);

    const Task& add(std::string title, Priority priority, std::string due);
    bool markDone(int id);
    bool remove(int id);
    void sortBy(const std::string& key);   // "id", "priority", "due"; throws std::invalid_argument otherwise

    const std::vector<Task>& all() const { return tasks; }

private:
    void load();
    void save() const;   // called after every change

    std::string path;
    std::vector<Task> tasks;
    int nextId{1};
};
