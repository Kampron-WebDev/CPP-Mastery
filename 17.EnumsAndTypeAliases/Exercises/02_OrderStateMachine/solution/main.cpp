#include <iostream>
#include <iomanip>
#include <string_view>

using Money = long long;   // amounts in cents

enum class OrderState { Created, Paid, Shipped, Delivered, Cancelled, Refunded };
enum class Event { Pay, Ship, Deliver, Cancel, Refund };

std::string_view toString(OrderState s)
{
    switch (s) {
        using enum OrderState;
        case Created:   return "Created";
        case Paid:      return "Paid";
        case Shipped:   return "Shipped";
        case Delivered: return "Delivered";
        case Cancelled: return "Cancelled";
        case Refunded:  return "Refunded";
    }
    return "?";
}

std::string_view toString(Event e)
{
    switch (e) {
        using enum Event;
        case Pay:     return "Pay";
        case Ship:    return "Ship";
        case Deliver: return "Deliver";
        case Cancel:  return "Cancel";
        case Refund:  return "Refund";
    }
    return "?";
}

// Every legal transition is listed once: easy to read, easy to extend.
OrderState handle(OrderState current, Event e, bool& ok)
{
    using enum OrderState;
    ok = true;
    if (current == Created && e == Event::Pay)     return Paid;
    if (current == Created && e == Event::Cancel)  return Cancelled;
    if (current == Paid    && e == Event::Ship)    return Shipped;
    if (current == Paid    && e == Event::Refund)  return Refunded;
    if (current == Shipped && e == Event::Deliver) return Delivered;
    ok = false;
    return current;
}

int main()
{
    const Money total{4999};
    // setw(2)+setfill('0') so 4905 prints as 49.05, not 49.5
    std::cout << "Order total: " << total / 100 << '.' << std::setw(2) << std::setfill('0')
              << total % 100 << std::setfill(' ') << '\n';

    OrderState state{OrderState::Created};
    for (Event e : {Event::Pay, Event::Ship, Event::Cancel, Event::Deliver, Event::Refund}) {
        bool ok{};
        const OrderState next = handle(state, e, ok);
        if (ok) std::cout << toString(state) << " --" << toString(e) << "--> " << toString(next) << '\n';
        else    std::cout << "illegal: can't " << toString(e) << " when " << toString(state) << '\n';
        state = next;
    }
}
