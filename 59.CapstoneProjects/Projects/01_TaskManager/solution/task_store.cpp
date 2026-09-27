#include "task_store.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

TaskStore::TaskStore(std::string filePath) : path{std::move(filePath)} { load(); }

const Task& TaskStore::add(std::string title, Priority priority, std::string due)
{
    tasks.push_back(Task{nextId++, std::move(title), priority, std::move(due), false});
    save();
    return tasks.back();
}

bool TaskStore::markDone(int id)
{
    const auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& t) { return t.id == id; });
    if (it == tasks.end()) return false;
    it->done = true;
    save();
    return true;
}

bool TaskStore::remove(int id)
{
    const auto removed = std::erase_if(tasks, [id](const Task& t) { return t.id == id; });
    if (removed) save();
    return removed > 0;
}

void TaskStore::sortBy(const std::string& key)
{
    if (key == "id") {
        std::ranges::sort(tasks, {}, &Task::id);
    } else if (key == "priority") {
        std::ranges::stable_sort(tasks, std::greater{}, &Task::priority);   // High first
    } else if (key == "due") {
        // Tasks without a due date go last; "YYYY-MM-DD" strings sort correctly as text.
        std::ranges::stable_sort(tasks, [](const Task& a, const Task& b) {
            if (a.due.empty() != b.due.empty()) return b.due.empty();
            return a.due < b.due;
        });
    } else {
        throw std::invalid_argument{"unknown sort key '" + key + "' (use id, priority or due)"};
    }
    save();
}

// File format: one task per line, TAB-separated: id, done, priority, due, title
void TaskStore::load()
{
    std::ifstream in{path};
    if (!in) return;   // first run: no file yet
    for (std::string line; std::getline(in, line);) {
        std::istringstream fields{line};
        std::string id, done, priority, due, title;
        if (!std::getline(fields, id, '\t') || !std::getline(fields, done, '\t') ||
            !std::getline(fields, priority, '\t') || !std::getline(fields, due, '\t') || !std::getline(fields, title))
            continue;   // skip corrupt lines rather than crash
        try {
            Task t{std::stoi(id), title, parsePriority(priority).value_or(Priority::Medium), due, done == "1"};
            nextId = std::max(nextId, t.id + 1);   // ids are never reused
            tasks.push_back(std::move(t));
        } catch (const std::exception&) {
            continue;
        }
    }
}

void TaskStore::save() const
{
    // Write to a temporary file first, then replace: a crash can't leave a half-written file.
    const std::string temp = path + ".tmp";
    {
        std::ofstream out{temp};
        if (!out) throw std::runtime_error{"cannot write " + temp};
        for (const auto& t : tasks)
            out << t.id << '\t' << (t.done ? 1 : 0) << '\t' << toString(t.priority) << '\t' << t.due << '\t' << t.title << '\n';
    }
    std::remove(path.c_str());
    std::rename(temp.c_str(), path.c_str());
}
