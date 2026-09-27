// Strategy: choose HOW something is done at run time. Two styles: interface and std::function.
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ---- Classic OOP style ----
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual double apply(double price) const = 0;
    virtual std::string name() const = 0;
};

class NoDiscount : public PricingStrategy {
public:
    double apply(double price) const override { return price; }
    std::string name() const override { return "regular"; }
};

class PercentOff : public PricingStrategy {
public:
    explicit PercentOff(double pct) : pct{pct} {}
    double apply(double price) const override { return price * (1 - pct / 100); }
    std::string name() const override { return std::to_string(static_cast<int>(pct)) + "% off"; }
private:
    double pct;
};

class Checkout {
public:
    explicit Checkout(std::unique_ptr<PricingStrategy> s) : strategy{std::move(s)} {}
    void setStrategy(std::unique_ptr<PricingStrategy> s) { strategy = std::move(s); }   // swap at run time
    void pay(double price) const { std::cout << strategy->name() << ": " << strategy->apply(price) << '\n'; }
private:
    std::unique_ptr<PricingStrategy> strategy;
};

int main()
{
    Checkout checkout{std::make_unique<NoDiscount>()};
    checkout.pay(100);
    checkout.setStrategy(std::make_unique<PercentOff>(25));   // Black Friday!
    checkout.pay(100);

    // ---- Modern style: a strategy is just a callable ----
    std::vector<std::pair<std::string, std::function<double(double)>>> strategies{
        {"regular", [](double p) { return p; }},
        {"half price", [](double p) { return p / 2; }},
        {"$10 off (min $0)", [](double p) { return p > 10 ? p - 10 : 0.0; }},
    };
    for (const auto& [name, rule] : strategies) std::cout << name << ": " << rule(100) << '\n';
}
