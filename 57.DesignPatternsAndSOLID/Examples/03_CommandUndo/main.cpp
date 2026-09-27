// Command pattern: every action is an object that knows how to execute AND undo itself.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Document {
public:
    std::string text;
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Document& doc) = 0;
    virtual void undo(Document& doc) = 0;
};

class Append : public Command {
public:
    explicit Append(std::string s) : added{std::move(s)} {}
    void execute(Document& doc) override { doc.text += added; }
    void undo(Document& doc) override { doc.text.erase(doc.text.size() - added.size()); }
private:
    std::string added;
};

class Uppercase : public Command {
public:
    void execute(Document& doc) override
    {
        before = doc.text;   // remember what we need to undo
        for (char& c : doc.text) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    void undo(Document& doc) override { doc.text = before; }
private:
    std::string before;
};

class Editor {
public:
    void run(std::unique_ptr<Command> cmd)
    {
        cmd->execute(doc);
        history.push_back(std::move(cmd));
        redoStack.clear();
        show();
    }
    void undo()
    {
        if (history.empty()) return;
        history.back()->undo(doc);
        redoStack.push_back(std::move(history.back()));
        history.pop_back();
        show();
    }
    void redo()
    {
        if (redoStack.empty()) return;
        redoStack.back()->execute(doc);
        history.push_back(std::move(redoStack.back()));
        redoStack.pop_back();
        show();
    }

private:
    void show() const { std::cout << "[" << doc.text << "]\n"; }
    Document doc;
    std::vector<std::unique_ptr<Command>> history, redoStack;
};

int main()
{
    Editor editor;
    editor.run(std::make_unique<Append>("hello"));
    editor.run(std::make_unique<Append>(" world"));
    editor.run(std::make_unique<Uppercase>());
    editor.undo();
    editor.undo();
    editor.redo();
}
