# Lesson 54: Data Structures and Algorithms ⭐ NEW

> **In one sentence:** Data structures are **ways to organise data**, algorithms are **recipes
> to process it**, and **Big-O** tells you how a recipe slows down as the data grows. This is
> what separates code that works on 100 items from code that works on 100 million.

This is the most asked-about topic in software engineering interviews, and it makes you a much stronger designer.

---

## 🎯 You will learn

- **Big-O notation**: O(1), O(log n), O(n), O(n log n), O(n²), O(2ⁿ).
- Linked lists, stacks, queues, hash tables, binary search trees, heaps, graphs.
- Binary search.
- Sorting: insertion, merge, quick sort.
- Graph search: BFS and DFS.
- Problem-solving patterns: two pointers, sliding window, hashing, recursion, **dynamic programming**.

---

## 🧸 The Big Idea: finding a name in a phone book

You need "Mensah" in a phone book with 1 000 000 names:

| Method | Steps (worst case) | Big-O |
|--------|-------------------|-------|
| Read every name from the start | 1 000 000 | **O(n)**: linear |
| Open the middle; go left or right; repeat | 20 | **O(log n)**: logarithmic |
| A magic index: "M names start on page 612" | 1 | **O(1)**: constant |

Big-O describes **how the work grows** when the input grows, ignoring constant details:

```
 n =          10        1 000        1 000 000
 O(1)          1            1                1
 O(log n)      3           10               20
 O(n)         10        1 000        1 000 000
 O(n log n)   33       10 000       20 000 000
 O(n²)       100    1 000 000    1 000 000 000 000   ← 11 days at 1 billion ops/sec!
 O(2ⁿ)     1 024    (way too many to compute)
```
**Rule of thumb for spotting it:** one loop over n → O(n). A loop inside a loop over n → O(n²). Halving each step → O(log n).

---

## 📚 The structures

| Structure | Picture | Access | Search | Insert/Delete | In C++ |
|-----------|---------|--------|--------|---------------|--------|
| Array / vector | lockers in a row | O(1) | O(n) (O(log n) if sorted) | O(n) (end: O(1)) | `std::vector` |
| Linked list | treasure hunt clues | O(n) | O(n) | O(1) at a known spot | `std::list` |
| Stack | pile of plates | top only | – | O(1) | `std::stack` |
| Queue | shop line | front only | – | O(1) | `std::queue` |
| Hash table | coat check tickets | – | **O(1)** avg | O(1) avg | `std::unordered_map` |
| Balanced BST | family tree, sorted | – | O(log n) | O(log n) | `std::map`, `std::set` |
| Heap | tournament bracket | max in O(1) | – | O(log n) | `std::priority_queue` |
| Graph | map of cities & roads | – | BFS/DFS O(V+E) | – | `vector<vector<int>>` adjacency list |

Build them yourself once to really understand them:
- [Examples/02_LinkedList](Examples/02_LinkedList/main.cpp): a singly linked list with `unique_ptr` nodes.
- [Examples/03_BinarySearchTree](Examples/03_BinarySearchTree/main.cpp): insert, search, in-order traversal (sorted output!).

## 📚 The algorithms

### Binary search: O(log n) (needs **sorted** data)
```cpp
int lo = 0, hi = n - 1;
while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;          // not (lo+hi)/2: that can overflow
    if (a[mid] == target) return mid;
    if (a[mid] < target) lo = mid + 1; else hi = mid - 1;
}
return -1;
```

### Sorting ([Examples/04_SortingAlgorithms](Examples/04_SortingAlgorithms/main.cpp))
| Algorithm | Idea | Time | Notes |
|-----------|------|------|-------|
| Insertion sort | Like sorting cards in your hand | O(n²) | Great for tiny or nearly-sorted data |
| Merge sort | Split in half, sort each, **merge** | O(n log n) always | Stable, needs extra memory |
| Quick sort | Pick a pivot, smaller left / bigger right, recurse | O(n log n) avg | In place; `std::sort` uses a hybrid (introsort) |

### Graphs: BFS and DFS ([Examples/05_GraphBFS](Examples/05_GraphBFS/main.cpp))
- **BFS** (breadth-first, with a queue): explores in "rings" → finds the **shortest path** in unweighted graphs.
- **DFS** (depth-first, with recursion/stack): goes deep first → cycles, connectivity, mazes.

### Problem-solving patterns (interview gold)
| Pattern | Use when | Example |
|---------|----------|---------|
| **Hashing** | "have I seen X?" | Two Sum in O(n) instead of O(n²) |
| **Two pointers** | sorted arrays, pairs, reversing | Palindrome check, pair with sum |
| **Sliding window** | contiguous sub-arrays | longest substring without repeats |
| **Recursion / divide & conquer** | problem splits into smaller copies | merge sort, trees |
| **Dynamic programming** | overlapping sub-problems | Fibonacci, climbing stairs, coin change |
| **Greedy** | local best choice is globally best | coin change with normal coins (Lesson 02!) |

---

## 🗂️ Examples

| Folder | Shows |
|--------|-------|
| [01_BigOTiming](Examples/01_BigOTiming/main.cpp) | O(n) vs O(n²) vs O(log n), measured |
| [02_LinkedList](Examples/02_LinkedList/main.cpp) | Singly linked list: push, remove, reverse |
| [03_BinarySearchTree](Examples/03_BinarySearchTree/main.cpp) | BST insert, contains, in-order walk, height |
| [04_SortingAlgorithms](Examples/04_SortingAlgorithms/main.cpp) | Insertion, merge, quick sort, compared with `std::sort` |
| [05_GraphBFS](Examples/05_GraphBFS/main.cpp) | BFS shortest path, DFS reachability |

## ⚠️ Common mistakes

- Off-by-one errors in binary search (`lo < hi` vs `lo <= hi`, `mid` vs `mid ± 1`). Trace it by hand on 1 and 2 elements!
- Recursion without memoization on overlapping sub-problems (exponential time).
- Ignoring the hidden O(n) inside a loop (`vector.erase(begin())`, `string +=` building, `std::find`) → accidental O(n²).

## 🧠 Senior developer notes

- In real code, **use the standard library** (`std::sort`, `std::unordered_map`, `std::lower_bound`). Implement structures yourself to *learn*, and in interviews.
- Big-O isn't everything: constants and **cache behaviour** matter. A `vector` often beats a `list` even where Big-O says otherwise (Lesson 58).
- Interview method: clarify → examples → brute force + its Big-O → optimise → code → test with edge cases. (That's Lesson 02's 4 steps!)

## ✅ Check yourself

1. What's the Big-O of: a loop over n with a nested loop over n? Binary search? Looking up in `std::unordered_map`?
2. Why must data be sorted for binary search?
3. Which traversal finds the shortest path in an unweighted graph?
4. What makes a problem suitable for dynamic programming?

<details><summary>Answers</summary>

1. O(n²); O(log n); O(1) average.
2. It throws away half the data each step based on comparisons, which only works if order tells you where the target must be.
3. BFS.
4. Overlapping sub-problems + optimal substructure (the answer builds from answers to smaller versions).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

Practise more at LeetCode / HackerRank / Codeforces (easy problems first, in C++).

**Next:** [Lesson 55: Testing, Debugging and Clean Code](../55.TestingDebuggingAndCleanCode/README.md)
