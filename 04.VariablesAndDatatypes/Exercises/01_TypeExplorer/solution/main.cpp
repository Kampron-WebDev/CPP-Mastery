#include <iostream>

int main()
{
    int studentCount{30};
    unsigned int pageViews{4'000'000'000u};   // ' is a digit separator (C++14)
    long long worldPopulation{8'100'000'000LL};
    float temperature{21.5f};
    double pi{3.141592653589793};
    bool isRaining{false};
    char grade{'A'};

    std::cout << std::boolalpha;
    std::cout << "studentCount    = " << studentCount << " (" << sizeof(studentCount) << " bytes)\n";
    std::cout << "pageViews       = " << pageViews << " (" << sizeof(pageViews) << " bytes)\n";
    std::cout << "worldPopulation = " << worldPopulation << " (" << sizeof(worldPopulation) << " bytes)\n";
    std::cout << "temperature     = " << temperature << " (" << sizeof(temperature) << " bytes)\n";
    std::cout << "pi              = " << pi << " (" << sizeof(pi) << " bytes)\n";
    std::cout << "isRaining       = " << isRaining << " (" << sizeof(isRaining) << " byte)\n";
    std::cout << "grade           = " << grade << " (" << sizeof(grade) << " byte)\n";
}
