# Lesson 44: Zooming in on STL Containers

> **In one sentence:** Each STL container is a different **shape of storage** with different
> strengths; choosing the right one (and knowing its costs) is a core senior skill.

---

## 🎯 You will learn

- Sequence containers: `deque`, `forward_list`, `list`, `vector`, `array`.
- `std::pair`.
- Associative containers: `set`, `map`, `multiset`, `multimap` (sorted trees).
- Unordered containers: `unordered_set`, `unordered_map` (hash tables).
- Container adaptors: `stack`, `queue`, `priority_queue`.

---

## 🧸 The Big Idea: different kinds of storage at home

| Container | Real-life picture | Great at |
|-----------|-------------------|----------|
| `vector` | A row of lockers, side by side | Fast access by number, adding at the end |
| `deque` | A row you can extend at **both** ends | Adding/removing at front AND back |
| `list` | A treasure hunt: each clue points to the next *and* previous | Inserting in the middle (if you're already there) |
| `forward_list` | Treasure hunt, forward clues only | Minimal memory list |
| `set` | A dictionary's word list: sorted, no duplicates | "Is X in here?" in sorted order |
| `map` | A phone book: name → number, sorted by name | Lookup by key |
| `unordered_map` | A coat check: ticket number → coat, no order | **Fastest** lookup by key |
| `stack` | A pile of plates (last in, first out) | Undo, brackets, backtracking |
| `queue` | A line at the shop (first in, first out) | Tasks in arrival order |
| `priority_queue` | Hospital emergency room: most urgent first | Scheduling, Dijkstra |

---

## 📚 Step by step

### Sequence containers ([44.2](44.2Deque/main.cpp)–[44.6](44.6Array/main.cpp))

| Operation | `vector` | `deque` | `list` |
|-----------|---------|---------|--------|
| Access `[i]` | O(1) | O(1) | ❌ (walk: O(n)) |
| Add/remove at end | O(1)* | O(1) | O(1) |
| Add/remove at front | O(n) | O(1) | O(1) |
| Insert in middle | O(n) | O(n) | O(1) if you have the iterator |
| Memory | contiguous ✅ | chunks | scattered nodes |
(*amortized. Big-O is explained in Lesson 54: O(1) = instant, O(n) = grows with size.)

### `std::pair` ([44.8Pair](44.8Pair/main.cpp))
`std::pair<std::string, int> p{"Ama", 90};` → `p.first`, `p.second`, or `auto [name, score] = p;`

### Sorted associative ([44.9Set](44.9Set/main.cpp), [44.10Map](44.10Map/main.cpp), [44.11](44.11MultisetMultimap/main.cpp))
Balanced trees: operations are **O(log n)**, and iteration is **in sorted order**.
```cpp
std::map<std::string, int> ages;
ages["Kofi"] = 30;                 // insert or overwrite
if (auto it = ages.find("Ama"); it != ages.end()) std::cout << it->second;
ages.contains("Kofi");             // C++20
for (const auto& [name, age] : ages) ...   // sorted by name
```
⚠️ `ages["Unknown"]` **inserts** a default value (0) if missing! Use `find`/`contains` just to look.
`multiset`/`multimap` allow duplicate keys.

### Hash containers ([44.12](44.12UnorderedSetUnorderedMap/main.cpp))
Average **O(1)** lookup, no order. Your go-to for "count things" and "have I seen this?".

### Adaptors ([44.14Stack](44.14Stack/main.cpp), [44.15Queue](44.15Queue/main.cpp), [44.16PriorityQueue](44.16PriorityQueue/main.cpp))
Restricted interfaces on top of other containers: `push`, `pop`, `top`/`front`.
`priority_queue` is a max-heap by default; use `std::greater<>` for a min-heap.

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [44.2Deque](44.2Deque/main.cpp) | Double-ended queue |
| [44.3ForwardList](44.3ForwardList/main.cpp) | Singly linked list |
| [44.4List](44.4List/main.cpp) | Doubly linked list |
| [44.5Vector](44.5Vector/main.cpp) | Vector in depth |
| [44.6Array](44.6Array/main.cpp) | `std::array` in depth |
| [44.8Pair](44.8Pair/main.cpp) | `std::pair` |
| [44.9Set](44.9Set/main.cpp) | Sorted unique set |
| [44.10Map](44.10Map/main.cpp) | Sorted key → value |
| [44.11MultisetMultimap](44.11MultisetMultimap/main.cpp) | Duplicates allowed |
| [44.12UnorderedSetUnorderedMap](44.12UnorderedSetUnorderedMap/main.cpp) | Hash tables |
| [44.14Stack](44.14Stack/main.cpp) | LIFO |
| [44.15Queue](44.15Queue/main.cpp) | FIFO |
| [44.16PriorityQueue](44.16PriorityQueue/main.cpp) | Heap |

## ⚠️ Common mistakes

- `map[key]` to *check* existence (it inserts!).
- Using `list` "because inserting is O(1)". Finding the spot is O(n), and the cache misses make it slow. Measure!
- Modifying a `set` element in place (it would break the sorting; not allowed).

## 🧠 Senior developer notes

- **Choosing a container** (ask in this order):
  1. Default: `vector`.
  2. Lookup by key? `unordered_map` (fast) or `map` (need sorted order / ordered range queries).
  3. Unique membership? `unordered_set` / `set`.
  4. Queue-like behaviour? `deque` / `queue` / `priority_queue`.
  5. `list` only with a measured reason.
- Custom types as keys: `map` needs `<` (or `<=>`); `unordered_map` needs `==` and a hash function.

## ✅ Check yourself

1. Which container for "count how many times each word appears"?
2. What's the lookup cost of `std::map` vs `std::unordered_map`?
3. What does `std::stack` use underneath by default?

<details><summary>Answers</summary>

1. `std::unordered_map<std::string, int>` (or `std::map` if you want the words sorted).
2. O(log n) vs O(1) average.
3. `std::deque`.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 45: STL Algorithms](../45.StlAlgorithms/README.md)
