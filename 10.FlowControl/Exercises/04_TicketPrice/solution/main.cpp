#include <iostream>
#include <iomanip>
#include <algorithm>   // std::max

// Test plan (age, student, day -> price):
//   30 n 1 -> 12.00      (no discount)
//    8 n 1 ->  6.00      (child 50%)
//   70 n 1 ->  8.40      (senior 30%)
//   20 y 1 ->  9.60      (student 20%)
//    8 y 1 ->  6.00      (child: student discount does NOT stack)
//   20 y 2 ->  7.60      (student + Tuesday)
//    8 n 2 ->  4.00      (child + Tuesday)
//    3 n 2 ->  4.00      (same; floor of 3.00 not reached)
//  130 n 1 -> error

constexpr double basePrice{12.00};
constexpr double tuesdayDiscount{2.00};
constexpr double minimumPrice{3.00};

double discountRate(int age, bool isStudent)
{
    if (age < 12) return 0.50;
    if (age >= 65) return 0.30;
    if (isStudent && age <= 25) return 0.20;
    return 0.0;
}

int main()
{
    int age{}, day{};
    char studentAnswer{};
    std::cout << "Age, student (y/n), day (1-7): ";
    std::cin >> age >> studentAnswer >> day;

    if (!std::cin || age < 0 || age > 120 || day < 1 || day > 7) {
        std::cout << "Error: invalid input\n";
        return 1;
    }
    const bool isStudent = (studentAnswer == 'y' || studentAnswer == 'Y');

    double price = basePrice * (1.0 - discountRate(age, isStudent));
    if (day == 2) {
        price = std::max(price - tuesdayDiscount, minimumPrice);
    }

    std::cout << std::fixed << std::setprecision(2) << "Price: " << price << '\n';
}
