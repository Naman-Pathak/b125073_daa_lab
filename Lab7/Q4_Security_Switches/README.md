# Q4 — Security Switches

## Problem
There are `n` switches, initially all ON.

Rules:
- The rightmost switch can always be toggled.
- Any other switch can be toggled only when its immediate right neighbor is ON and every switch farther to its right is OFF.
- Only one switch changes per move.

Goal: turn all switches OFF in the minimum number of moves.

## Important observation
The legal states and moves have the same flavor as a binary-counter / Gray-code traversal: only a very restricted switch can be changed at each step.

Let `dp[n]` be the minimum number of moves needed to turn off `n` initially-ON switches.

The optimal counts satisfy:

- `dp[1] = 1`
- `dp[2] = 2`
- for `n >= 3`:

`dp[n] = 2*dp[n-1] + (n mod 2)`.

Therefore the sequence is:

`1, 2, 5, 10, 21, 42, 85, ...`

The equivalent compact formula is

`dp[n] = floor(2^(n+1) / 3)`.

## Why the recurrence makes sense
Consider the leftmost switch. Before it can be turned OFF, the switches to its right must reach the unique configuration that makes that toggle legal. This forces essentially a full optimal solution for a smaller prefix, followed by the remaining required transitions, and the same structure appears again on the way back.

The parity of `n` determines whether one extra toggle is necessary, giving the `+ (n mod 2)` term.

## Dynamic-programming algorithm
1. Set `dp[1] = 1` and `dp[2] = 2`.
2. For `i = 3..n`, compute:
   `dp[i] = 2*dp[i-1] + (i mod 2)`.
3. Print `dp[n]`.

## Complexity
- Time: `O(n)`
- Space: `O(n)` for the DP table.

The answer itself can also be computed directly from the closed form in `O(1)` time, but the DP recurrence is clearer for the lab's requested approach.

## C compilation
```bash
gcc q4.c -o q4
./q4
```

For example, `n = 4` gives `10` moves.
