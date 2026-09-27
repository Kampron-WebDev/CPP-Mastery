// Task Manager CLI: reference solution. main.cpp only parses commands and prints;
// storage and sorting live in TaskStore (separation of concerns).
#include <algorithm>
#include <format>
#include <iostream>
#include <sstream>
#include <string>

#include "task_store.h"

namespace {

std::string trim(const std::string& s)
{
    const auto first = s.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    return s.substr(first, s.find_last_not_of(" \t") - first + 1);
}

void printTasks(const TaskStore& store, bool pendingOnly, const std::string& filter = "")
{
    std::cout << std::format("{:>3}  {:<4}  {:<8}  {:<10}  {}\n", "#", "Done", "Priority", "Due", "Title");
    int shown = 0;
    for (const auto& t : store.all()) {
        if (pendingOnly && t.done) continue;
        if (!filter.empty() && t.title.find(filter) == std::string::npos) continue;
        std::cout << std::format("{:>3}  {:<4}  {:<8}  {:<10}  {}\n", t.id, t.done ? "[x]" : "[ ]", toString(t.priority),
                                 t.due.empty() ? "-" : t.due, t.title);
        ++shown;
    }
    if (shown == 0) std::cout << "  (no tasks)\n";
}

void printHelp()
{
    std::cout << "Commands:\n"
                 "  add <title> [| low/medium/high [| YYYY-MM-DD]]\n"
                 "  list [--pending]     find <text>     stats\n"
                 "  done <id>            remove <id>     sort <id|priority|due>\n"
                 "  help                 quit\n";
}

// "add Buy milk | high | 2026-10-01"
void handleAdd(TaskStore& store, const std::string& args)
{
    std::istringstream parts{args};
    std::string title, priorityText, due;
    std::getline(parts, title, '|');
    std::getline(parts, priorityText, '|');
    std::getline(parts, due);
    title = trim(title);
    priorityText = trim(priorityText);
    due = trim(due);

    if (title.empty()) throw std::invalid_argument{"a task needs a title"};
    Priority priority = Priority::Medium;
    if (!priorityText.empty()) {
        const auto parsed = parsePriority(priorityText);
        if (!parsed) throw std::invalid_argument{"priority must be low, medium or high"};
        priority = *parsed;
    }
    if (!due.empty() && (due.size() != 10 || due[4] != '-' || due[7] != '-'))
        throw std::invalid_argument{"due date must look like YYYY-MM-DD"};

    std::cout << "Added task #" << store.add(title, priority, due).id << '\n';
}

int parseId(const std::string& text)
{
    // std::stoi's own error messages ("stoi") mean nothing to a user, so translate them.
    try {
        std::size_t used = 0;
        const int id = std::stoi(text, &used);
        if (used == text.size()) return id;
    } catch (const std::exception&) {
    }
    throw std::invalid_argument{"task id must be a whole number, e.g. 'done 3'"};
}

}  // namespace

int main()
{
    TaskStore store{"tasks.txt"};
    std::cout << "Task Manager: " << store.all().size() << " task(s) loaded. Type 'help'.\n";

    for (std::string line; std::cout << "> " && std::getline(std::cin, line);) {
        std::istringstream in{line};
        std::string command;
        in >> command;
        std::string args;
        std::getline(in, args);
        args = trim(args);

        try {
            if (command == "quit" || command == "exit") break;
            else if (command.empty()) continue;
            else if (command == "help") printHelp();
            else if (command == "add") handleAdd(store, args);
            else if (command == "list") printTasks(store, args == "--pending");
            else if (command == "find") printTasks(store, false, args);
            else if (command == "done") std::cout << (store.markDone(parseId(args)) ? "Marked as done\n" : "No such task\n");
            else if (command == "remove") std::cout << (store.remove(parseId(args)) ? "Removed\n" : "No such task\n");
            else if (command == "sort") { store.sortBy(args); printTasks(store, false); }
            else if (command == "stats") {
                const auto& all = store.all();
                const auto done = std::ranges::count_if(all, &Task::done);
                std::cout << std::format("{} total, {} done, {} pending, {:.0f}% complete\n", all.size(), done,
                                         all.size() - static_cast<std::size_t>(done),
                                         all.empty() ? 0.0 : 100.0 * static_cast<double>(done) / static_cast<double>(all.size()));
            } else std::cout << "Unknown command. Type 'help'.\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
    std::cout << "Bye! Your tasks are saved in tasks.txt\n";
}
