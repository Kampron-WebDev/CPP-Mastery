// ⭐⭐ Exercise 03: LoanCalculator
// Read: loan amount P, yearly interest rate in percent (e.g. 5.5), and number of years.
// Compute the monthly payment:
//     r = rate / 12 / 100          (monthly rate as a fraction)
//     n = years * 12               (number of payments)
//     M = P * r * (1+r)^n / ((1+r)^n - 1)
// Print M, the total paid (M * n) and the total interest, all with exactly 2 decimals.
//   Input : 10000 5 3
//   Output: Monthly: 299.71 | Total: 10789.52 | Interest: 789.52
// Edge case: what if the rate is 0? (Then M = P / n.)
#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    // TODO
}
