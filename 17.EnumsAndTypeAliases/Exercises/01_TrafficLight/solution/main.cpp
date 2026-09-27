#include <iostream>
#include <string_view>

enum class Light { Red, Amber, Green };

std::string_view toString(Light l)
{
    switch (l) {
        using enum Light;
        case Red:   return "Red";
        case Amber: return "Amber";
        case Green: return "Green";
    }
    return "?";   // unreachable, but keeps the compiler happy
}

Light next(Light l)
{
    switch (l) {
        using enum Light;
        case Red:   return Green;
        case Green: return Amber;
        case Amber: return Red;
    }
    return Light::Red;
}

int main()
{
    Light light{Light::Red};
    for (int step = 0; step < 7; ++step) {
        std::cout << toString(light) << (step < 6 ? ", " : "\n");
        light = next(light);
    }
}
