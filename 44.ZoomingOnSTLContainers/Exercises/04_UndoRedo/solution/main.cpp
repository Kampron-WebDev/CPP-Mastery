#include <iostream>
#include <stack>
#include <string>

int main()
{
    std::string text;
    std::stack<std::string> undo, redo;   // each holds snapshots of previous texts

    for (std::string cmd; std::cout << "> " && std::cin >> cmd && cmd != "quit";) {
        if (cmd == "type") {
            std::string word;
            std::cin >> word;
            undo.push(text);
            text += (text.empty() ? "" : " ") + word;
            redo = {};                          // new edit: the redo future is gone
        } else if (cmd == "undo") {
            if (undo.empty()) { std::cout << "nothing to undo\n"; continue; }
            redo.push(text);
            text = undo.top();
            undo.pop();
        } else if (cmd == "redo") {
            if (redo.empty()) { std::cout << "nothing to redo\n"; continue; }
            undo.push(text);
            text = redo.top();
            redo.pop();
        } else if (cmd != "show") {
            std::cout << "commands: type <word>, undo, redo, show, quit\n";
            continue;
        }
        std::cout << "[" << text << "]\n";
    }
}
