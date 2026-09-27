#include <iostream>
#include <iomanip>

int main()
{
    int correct = 45;
    int total = 60;
    // correct / total was 0 (integer division) BEFORE multiplying by 100.
    double percent = static_cast<double>(correct) / total * 100.0;
    std::cout << "Score: " << percent << "%\n";

    correct = 47;
    percent = static_cast<double>(correct) / total * 100.0;
    std::cout << std::fixed << std::setprecision(1) << "Score: " << percent << "%\n";
}
