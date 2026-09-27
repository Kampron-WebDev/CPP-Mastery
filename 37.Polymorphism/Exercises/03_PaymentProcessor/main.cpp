// ⭐⭐⭐ Exercise 03: PaymentProcessor
// An online shop must support several payment methods, and more will come later.
// 1. Interface  class PaymentMethod { virtual bool pay(long long cents) = 0;
//                                     virtual std::string name() const = 0; virtual ~... }
// 2. Implementations: CreditCard (fails if over its limit), MobileMoney (fails if balance too low,
//    charges a 1% fee), GiftCard (single use: second pay fails).
// 3. class Checkout { void process(PaymentMethod& method, long long cents); }
//    It must NOT know about the concrete classes (no dynamic_cast, no if/else on type).
// 4. Simulate a few purchases, including failures, and print receipts.
#include <iostream>
#include <string>

int main()
{
    // TODO
}
