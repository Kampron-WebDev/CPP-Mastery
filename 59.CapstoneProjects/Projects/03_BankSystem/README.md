# Project 03: Bank System ⭐⭐

A menu-driven bank with different account types and a transaction history.

## Spec
- Account types (inheritance + polymorphism, Lesson 37):
  - `SavingsAccount`: earns monthly interest; max 3 withdrawals per month.
  - `CheckingAccount`: allows an overdraft down to a limit; monthly fee.
  - `FixedDeposit`: no withdrawals until its maturity month.
- Operations: open account, deposit, withdraw, transfer, month-end (apply interest/fees), statement, close account.
- Every operation is recorded as a `Transaction { id, type, amountCents, balanceAfter, description }`.
- Errors are exceptions from a hierarchy (`InsufficientFunds`, `AccountNotFound`, `LimitExceeded`, …), all caught in the menu.
- Money in **integer cents** (Lesson 04/34).
- Save and load all accounts to a file.

## Milestones
1. Abstract `Account` + one concrete type, deposit/withdraw with validation.
2. All three types via `std::vector<std::unique_ptr<Account>>`; `monthEnd()` is virtual.
3. Transfers with the **strong exception guarantee** (Lesson 38's exercise).
4. Transaction history + statement printing with `std::format`.
5. Persistence.

## Definition of done
- [ ] Balance invariants hold for every account type (tests!).
- [ ] No `dynamic_cast`: behaviour differences are virtual functions.
- [ ] Transfers are all-or-nothing.

Starter: [main.cpp](main.cpp)
