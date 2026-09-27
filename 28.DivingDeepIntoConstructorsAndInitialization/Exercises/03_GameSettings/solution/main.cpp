#include <iostream>
#include <string>

struct GameSettings {
    int width{1280};
    int height{720};
    bool fullscreen{false};
    int volume{80};
    std::string playerName{"Player1"};
};

void print(const GameSettings& s)
{
    std::cout << s.playerName << ": " << s.width << 'x' << s.height
              << (s.fullscreen ? " fullscreen" : " windowed") << ", volume " << s.volume << '\n';
}

int main()
{
    GameSettings defaults{};
    GameSettings hd{.width = 1920, .height = 1080, .fullscreen = true};
    GameSettings quiet{.volume = 0, .playerName = "Ada"};   // order must follow the declaration

    print(defaults);
    print(hd);
    print(quiet);
}
