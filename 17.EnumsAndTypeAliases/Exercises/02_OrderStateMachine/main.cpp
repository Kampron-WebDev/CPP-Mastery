// ⭐⭐⭐ Exercise 02: OrderStateMachine
// An online order moves through states:
//     Created -> Paid -> Shipped -> Delivered
//     Created -> Cancelled,   Paid -> Refunded
// Events: Pay, Ship, Deliver, Cancel, Refund
// 1. Make   enum class OrderState   and   enum class Event.
// 2. Write  OrderState handle(OrderState current, Event e, bool& ok)
//    - returns the new state; sets ok=false (and keeps the state) for an ILLEGAL move
//      e.g. Ship while Created, Refund after Delivered.
// 3. Run the event list below and print each transition or "illegal: ..." messages.
// Use a type alias:  using Money = long long; // cents   for an order total of 4999.
#include <iostream>

int main()
{
    // Events to run: Pay, Ship, Cancel, Deliver, Refund
    // TODO
}
