# Lesson 54 Exercises: Interview-Style Problems

For each: first write the **brute force** and its Big-O, then improve it. Write the Big-O of your final solution in a comment.

| # | Exercise | Level | Pattern |
|---|----------|-------|---------|
| 01 | [BinarySearch](01_BinarySearch/main.cpp) | ⭐⭐ | Halving, off-by-one care |
| 02 | [TwoSum](02_TwoSum/main.cpp) | ⭐⭐ | Hashing: O(n²) → O(n) |
| 03 | [ReverseAndMiddle](03_ReverseAndMiddle/main.cpp) | ⭐⭐ | Two pointers on a linked list |
| 04 | [LongestUniqueSubstring](04_LongestUniqueSubstring/main.cpp) | ⭐⭐⭐ | Sliding window |
| 05 | [ClimbingStairs](05_ClimbingStairs/main.cpp) | ⭐⭐ | Dynamic programming |
| 06 | [MazeSolver](06_MazeSolver/main.cpp) | ⭐⭐⭐ | BFS on a grid |

<details><summary>Hint for 02</summary>

For each number x, the partner you need is `target - x`. Have you *already seen* it? An `unordered_map<int,int>` of value → index answers that in O(1).
</details>
<details><summary>Hint for 04</summary>

Keep a window [left, right] with no repeated characters. Move `right` forward; when a repeat enters, move `left` just past the previous occurrence of that character.
</details>
<details><summary>Hint for 05</summary>

To reach step n you arrive from step n-1 (one step) or n-2 (two steps): `ways(n) = ways(n-1) + ways(n-2)`. Sound familiar?
</details>
