#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Button {
public:
    explicit Button(std::string label) : label{std::move(label)} {}
    void onClick(std::function<void(const std::string&)> handler) { handlers.push_back(std::move(handler)); }
    void click()
    {
        for (auto& handler : handlers) handler(label);
    }

private:
    std::string label;
    std::vector<std::function<void(const std::string&)>> handlers;
};

class Logger {
public:
    void operator()(const std::string& label) { messages.push_back("log: " + label + " pressed"); }
    const std::vector<std::string>& all() const { return messages; }

private:
    std::vector<std::string> messages;
};

class Game {
public:
    void attachTo(Button& b)
    {
        b.onClick([this](const std::string&) { jump(); });   // `this` must outlive the button
    }
    int jumps() const { return jumpCount; }

private:
    void jump() { ++jumpCount; }
    int jumpCount{0};
};

int main()
{
    Button button{"Jump"};
    int clicks{0};
    auto logger = std::make_shared<Logger>();
    Game game;

    button.onClick([](const std::string& label) { std::cout << "Button " << label << " clicked\n"; });
    button.onClick([&clicks](const std::string&) { ++clicks; });
    button.onClick([logger](const std::string& label) { (*logger)(label); });   // shared ownership keeps it alive
    game.attachTo(button);

    for (int i = 0; i < 3; ++i) button.click();

    std::cout << "clicks counted: " << clicks << '\n';
    std::cout << "logger has " << logger->all().size() << " messages, first: " << logger->all().front() << '\n';
    std::cout << "game jumps: " << game.jumps() << '\n';
}
