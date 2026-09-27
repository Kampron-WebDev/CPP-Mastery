// ⭐⭐⭐ Exercise 01: NotificationService
// This class breaks several SOLID principles. Refactor it:
//   - Create an interface  Notifier { virtual void send(const std::string& to, const std::string& msg) = 0; }
//   - Implementations: EmailNotifier, SmsNotifier, (then add) PushNotifier WITHOUT editing OrderService.
//   - OrderService receives its notifiers from OUTSIDE (constructor injection) instead of creating them.
//   - Write a FakeNotifier that just records messages, and use it in a tiny "test" in main that
//     checks the right message was sent. (That's why Dependency Inversion matters: testability!)
#include <iostream>
#include <string>

class OrderService {
public:
    void placeOrder(const std::string& customer, const std::string& channel)
    {
        std::cout << "Order saved for " << customer << '\n';
        if (channel == "email") {
            std::cout << "[EMAIL to " << customer << "] Your order is confirmed\n";
        } else if (channel == "sms") {
            std::cout << "[SMS to " << customer << "] Your order is confirmed\n";
        } else {
            std::cout << "unknown channel\n";
        }
    }
};

int main()
{
    OrderService service;
    service.placeOrder("ama@example.com", "email");
    service.placeOrder("+233200000000", "sms");
}
