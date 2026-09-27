# Project 04: Library Manager ⭐⭐

Manage a small library: books, members, loans and due dates.

## Spec
- `Book { isbn, title, author, year, copies }`, `Member { id, name }`, `Loan { isbn, memberId, borrowed, due }`.
- Commands: add book, add member, search (title/author, case-insensitive, partial), borrow, return, list overdue, member report.
- Rules: max 3 loans per member; loan period 14 days; late fee per day; can't borrow if no copies left.
- Dates with `std::chrono::year_month_day` (C++20): `due = sys_days{borrowed} + days{14}`.
- Use the right containers: `std::unordered_map<std::string, Book>` by ISBN, `std::map` for sorted listings.
- Persist everything to CSV files (Lesson 50).

## Milestones
1. Books + search. 2. Members + borrow/return with the rules. 3. Dates and overdue fees. 4. Persistence. 5. Reports.

## Stretch
- Reservations queue per book (`std::queue`).
- Import a books CSV with 1 000 rows and make search fast.

Starter: [main.cpp](main.cpp)
