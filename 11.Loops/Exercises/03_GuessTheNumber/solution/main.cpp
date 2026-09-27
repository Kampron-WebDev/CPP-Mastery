#include <iostream>
#include <limits>

int main()
{
    constexpr int secret{37};
    constexpr int maxTries{7};

    int tries{0};
    while (tries < maxTries) {
        int guess{};
        std::cout << "Your guess: ";
        if (!(std::cin >> guess)) {
            if (std::cin.eof()) return 0;   // input closed (Ctrl+Z): stop cleanly
            std::cin.clear();   // reset the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   // throw away the bad line
            std::cout << "Numbers only!\n";
            continue;           // doesn't count as a try
        }
        ++tries;
        if (guess > secret)      std::cout << "Too high\n";
        else if (guess < secret) std::cout << "Too low\n";
        else {
            std::cout << "Correct! You needed " << tries << " tries.\n";
            return 0;
        }
    }
    std::cout << "Out of tries. The number was " << secret << ".\n";
}
