#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<std::string, std::string> book;
    std::cout << "Commands: add/update/find/remove <name> [number], list, prefix <p>, quit\n";

    for (std::string cmd; std::cout << "> " && std::cin >> cmd && cmd != "quit";) {
        if (cmd == "add" || cmd == "update") {
            std::string name, number;
            std::cin >> name >> number;
            const bool exists = book.contains(name);
            if (cmd == "add" && exists)        std::cout << name << " already exists\n";
            else if (cmd == "update" && !exists) std::cout << name << " not found\n";
            else { book[name] = number; std::cout << "saved\n"; }
        } else if (cmd == "find") {
            std::string name;
            std::cin >> name;
            if (auto it = book.find(name); it != book.end()) std::cout << it->first << ": " << it->second << '\n';
            else std::cout << "not found\n";
        } else if (cmd == "remove") {
            std::string name;
            std::cin >> name;
            std::cout << (book.erase(name) ? "removed\n" : "not found\n");
        } else if (cmd == "list") {
            for (const auto& [name, number] : book) std::cout << name << ": " << number << '\n';
        } else if (cmd == "prefix") {
            std::string p;
            std::cin >> p;
            // lower_bound jumps straight to the first name >= p (O(log n)), then walk while it still matches
            for (auto it = book.lower_bound(p); it != book.end() && it->first.starts_with(p); ++it)
                std::cout << it->first << ": " << it->second << '\n';
        } else {
            std::cout << "unknown command\n";
        }
    }
}
