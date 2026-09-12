# Q3 — Reve's Puzzle (Four-Peg Tower of Hanoi)

## Problem
There are four pegs and `n` disks of different sizes. Initially all disks are on the first peg, largest at the bottom. Move the whole tower to another peg, one disk at a time, never placing a larger disk on a smaller disk.

The lab asks for a method that solves the 8-disk instance in 33 moves and then generalizes it to `n` disks.

## Dynamic-programming idea
With four pegs, simply moving `n-1` disks recursively is no longer the best strategy. The standard Frame-Stewart idea is to choose a split `k`:

1. Move the top `k` smallest disks to an auxiliary peg using four pegs.
2. Move the remaining `n-k` larger disks to the destination using the ordinary 3-peg Tower of Hanoi method.
3. Move the `k` smallest disks from the auxiliary peg to the destination using four pegs.

Let

`dp[n] = minimum number of moves for n disks with four pegs`.

Then

`dp[n] = min over 1 <= k < n of (2*dp[k] + (2^(n-k) - 1))`.

The term `2^(n-k)-1` is the standard minimum number of moves for moving `n-k` disks with 3 pegs.

## Base cases
- `dp[0] = 0`
- `dp[1] = 1`

## Why the recurrence works
For a chosen split `k`, the small disks must be moved out of the way before the largest remaining disks can be transferred. The same `k` disks must later be moved onto the destination. Therefore the four-peg part costs `2*dp[k]` and the middle three-peg part costs `2^(n-k)-1`.

Dynamic programming tries every possible split and stores the best result, preventing repeated recomputation.

## 8-disk result
The DP values begin as:

`0, 1, 3, 5, 9, 13, 17, 25, 33`

Hence:

`dp[8] = 33`.

For 8 disks the optimal split is `k = 4`:

`dp[8] = 2*dp[4] + (2^4 - 1)`

`= 2*9 + 15`

`= 33`.

## General algorithm
1. Initialize `dp[0] = 0`, `dp[1] = 1`.
2. For each `n` from 2 to the requested number of disks:
3. Try every split `k` from 1 to `n-1`.
4. Compute `2*dp[k] + 2^(n-k)-1`.
5. Store the minimum and remember the best `k` in `bestSplit[n]`.
6. Use `bestSplit` recursively to print a move sequence.

## Complexity
The DP has `n` states and each state checks `O(n)` splits.

- DP time: `O(n^2)`
- DP space: `O(n)`
- Printing the entire sequence necessarily takes `O(number of moves)` time.

## C compilation
```bash
gcc q3.c -o q3
./q3
```

Enter `8` to validate the lab's required 33-move instance. The program prints the corresponding move sequence.

## Note on optimality
This is the standard Frame-Stewart recurrence for the four-peg puzzle and is the intended dynamic-programming generalization used for this lab.
