#include <iostream>
#include <bitset>

constexpr unsigned char canJump   = 1 << 0;
constexpr unsigned char canSwim   = 1 << 1;
constexpr unsigned char canFly    = 1 << 2;
constexpr unsigned char hasKey    = 1 << 3;
constexpr unsigned char invisible = 1 << 4;

void show(const char* label, unsigned char flags)
{
    std::cout << std::bitset<8>(flags) << "  " << label << '\n';
}

int main()
{
    unsigned char player{0};
    show("start", player);

    player |= canJump | canSwim | hasKey;   // set three bits at once
    show("jump + swim + key", player);

    player &= ~hasKey;                        // clear
    show("used the key", player);

    player ^= invisible;                      // toggle on
    show("potion #1 (invisible)", player);
    player ^= invisible;                      // toggle off
    show("potion #2 (visible again)", player);

    std::cout << std::boolalpha;
    std::cout << "Can fly?  " << ((player & canFly) != 0) << '\n';
    std::cout << "Can jump? " << ((player & canJump) != 0) << '\n';
}
