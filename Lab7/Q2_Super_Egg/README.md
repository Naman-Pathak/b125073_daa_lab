# Q2 — Super Egg Testing Experiment

## Problem
There are `E` identical eggs and `F` floors. We must determine the highest floor from which an egg can be dropped without breaking, minimizing the number of drops in the worst case.

The lab specifically asks for a generalized dynamic-programming solution for `E` eggs and `F` floors.

## State definition
Let

`dp[e][f] = minimum number of drops needed in the worst case with e eggs and f floors`.

We want `dp[E][F]`.

## Thinking about the first drop
Suppose we first drop an egg from floor `x`.

There are two possible outcomes:

1. **Egg breaks**: the critical floor is below `x`, so we have `e-1` eggs and `x-1` floors left.
   Cost: `dp[e-1][x-1]`.

2. **Egg survives**: the critical floor is above `x`, so we still have `e` eggs and `f-x` floors left.
   Cost: `dp[e][f-x]`.

Because we want a guarantee, we must prepare for the worse branch:

`max(dp[e-1][x-1], dp[e][f-x])`.

The current drop itself costs `1`, so for a fixed `x`:

`1 + max(dp[e-1][x-1], dp[e][f-x])`.

We try every possible first floor `x` and choose the minimum:

`dp[e][f] = 1 + min( max(dp[e-1][x-1], dp[e][f-x]) )`, for `1 <= x <= f`.

## Base cases
- `dp[e][0] = 0`: with no floors, no drops are needed.
- `dp[1][f] = f`: with one egg, the only safe strategy is linear search from the bottom.
- `dp[e][1] = 1`: one floor needs one drop.

## Why dynamic programming works
The same subproblems appear many times. For example, many choices of `x` repeatedly ask for `dp[e-1][x-1]` or `dp[e][f-x]`. By filling the table bottom-up, each subproblem is solved once and then reused.

## Original lab instance
For `E = 2` and `F = 100`, the program computes:

`dp[2][100] = 14`

So 14 drops are sufficient in the worst case, and no strategy can guarantee success in fewer than 14 drops.

## Algorithm
1. Create a DP table of size `(E+1) x (F+1)`.
2. Initialize the base cases.
3. For every `e = 2..E`:
4. For every `f = 2..F`:
5. Try every first-drop floor `x = 1..f`.
6. Compute `1 + max(dp[e-1][x-1], dp[e][f-x])`.
7. Keep the smallest value.
8. Print `dp[E][F]`.

## Complexity
There are `E*F` states, and each state tries up to `F` floors.

- Time: `O(E * F^2)`
- Space: `O(E * F)`

## C compilation
```bash
gcc q2.c -o q2
./q2
```

Example input:
```text
2 100
```

The program also prints the DP table, which is useful for lab validation.
