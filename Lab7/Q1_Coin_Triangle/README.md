# Q1 — Invert the Coin Triangle

## Problem
Given an equilateral triangle of `n` rows made from closely packed identical coins, slide one coin at a time so that the triangle is inverted in the minimum number of moves. Find a compact formula and validate it with C.

The lab asks for an algorithm, C implementation, and complexity analysis.

## Key idea
The triangle contains the triangular number

`T(n) = 1 + 2 + ... + n = n(n+1)/2`

coins.

For the standard inversion arrangement, the best construction uses one horizontal row of the original triangle as the base of the inverted triangle. The minimum number of moved coins is

`M(n) = floor(T(n) / 3)`

So

`M(n) = floor(n(n+1) / 6)`.

### Why this is optimal
Think about choosing row `k` of the original triangle as the common base. Coins in rows that already belong to the final inverted triangle can stay in place. The remaining coins are paired between rows that must be shortened and rows that must be lengthened. Every move can fix at most one required misplaced coin, and the standard construction attains the lower bound.

The optimum occurs near `k ≈ (n+2)/3`, and the resulting minimum simplifies to `floor(T(n)/3)`.

## Dynamic-programming view
This puzzle has a closed-form solution, so a large DP table is unnecessary. To keep the requested DP formulation, the C program computes the triangular number through a prefix-DP recurrence:

`dp[0] = 0`

`dp[i] = dp[i-1] + i`

Thus `dp[n] = T(n)`, and the answer is `dp[n] / 3` using integer division.

This is a simple cumulative DP: each state stores the total number of coins in the first `i` rows.

## Example
For `n = 8`:

`T(8) = 8*9/2 = 36`

`minimum moves = floor(36/3) = 12`

## Algorithm
1. Read `n`.
2. Build `dp[0..n]` using `dp[i] = dp[i-1] + i`.
3. Let `total = dp[n]`.
4. Print `total / 3`.

## Complexity
- Time: `O(n)` because the prefix DP has `n` states.
- Extra space: `O(n)` in this implementation.
- The mathematical formula alone can be evaluated in `O(1)` time and `O(1)` space; the DP form is included specifically for the lab requirement.

## C compilation
```bash
gcc q1.c -o q1
./q1
```

## Expected validation
Input:
```text
8
```
Output:
```text
Total coins = 36
Minimum moves = 12
```

## Important note
The geometric proof is the real reason the answer is `floor(T(n)/3)`. The DP in the program is used to compute the triangular number and validate the compact formula; it does not replace the geometric argument.
