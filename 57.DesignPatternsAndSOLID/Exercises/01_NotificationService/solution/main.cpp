#include <iostream>
#include <memory>
#include <string>
#include <vector>

// D: OrderService depends on this abstraction, not on concrete senders.
class Notifier {
public:
    virtual ~Notifier() = default;
    virtual void send(const std::string& to, const std::string& message) = 0;
};

class EmailNotifier : public Notifier {
public:
    void send(const std::string& to, const std::string& m) override { std::cout << "[EMAIL to " << to << "] " << m << '\n'; }
};

class SmsNotifier : public Notifier {
public:
    void send(const std::string& to, const std::string& m) override { std::cout << "[SMS to " << to << "] " << m << '\n'; }
};

// O: a new channel is a new class. OrderService is not edited.
class PushNotifier : public Notifier {
public:
    void send(const std::string& to, const std::string& m) override { std::cout << "[PUSH to " << to << "] " << m << '\n'; }
};

// S: OrderService handles orders; sending is someone else's job.
class OrderService {
public:
    explicit OrderService(Notifier& notifier) : notifier{notifier} {}   // injected from outside
    void placeOrder(const std::string& customer)
    {
        std::cout << "Order saved for " << customer << '\n';
        notifier.send(customer, "Your order is confirmed");
    }

private:
    Notifier& notifier;
};

// A test double: records instead of sending.
class FakeNotifier : public Notifier {
public:
    void send(const std::string& to, const std::string& m) override { sent.push_back(to + ": " + m); }
    std::vector<std::string> sent;
};

int main()
{
    EmailNotifier email;
    SmsNotifier sms;
    PushNotifier push;
    OrderService{email}.placeOrder("ama@example.com");
    OrderService{sms}.placeOrder("+233200000000");
    OrderService{push}.placeOrder("device-42");

    // "Unit test" with no real email/SMS involved:
    FakeNotifier fake;
    OrderService{fake}.placeOrder("test@example.com");
    const bool ok = fake.sent.size() == 1 && fake.sent[0] == "test@example.com: Your order is confirmed";
    std::cout << "test " << (ok ? "PASSED" : "FAILED") << '\n';
}
