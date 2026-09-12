# Q7 — Matrix Chain Multiplication (MCM)

## Problem
Given a chain of matrices, find:

1. the minimum number of scalar multiplications required to multiply all matrices, and
2. the parenthesization that achieves that minimum.

Matrix multiplication is associative, so the final result is the same, but the cost can vary dramatically depending on the order.

## Input representation
Suppose there are `n` matrices:

`A1, A2, ..., An`

and the dimension array is:

`p[0], p[1], ..., p[n]`

where:

`Ai` has dimensions `p[i-1] x p[i]`.

## DP state
Let

`dp[i][j] = minimum scalar multiplications needed to compute Ai...Aj`.

For one matrix there is no multiplication:

`dp[i][i] = 0`.

## Recurrence
Suppose the final multiplication splits the chain between `Ak` and `A(k+1)`.

The cost is:

`dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j]`.

Therefore:

`dp[i][j] = min over i <= k < j of`

`dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j]`.

We also store `split[i][j] = k` so that we can reconstruct the optimal parenthesization later.

## Thinking process
For a chain of length 2, there is only one possible multiplication.

For a longer chain, the last multiplication must split the chain into two smaller chains. Those smaller chains are exactly the same kind of problem, so their optimal costs are reusable DP subproblems.

This gives optimal substructure and overlapping subproblems — the two main properties that make dynamic programming appropriate.

## Algorithm
1. Read `n` and `p[0..n]`.
2. Set `dp[i][i] = 0`.
3. Consider chain lengths from 2 to `n`.
4. For each `(i, j)`, try every split `k` from `i` to `j-1`.
5. Store the minimum cost and its split point.
6. Reconstruct the parenthesization recursively using the `split` table.

## Complexity
There are `O(n^2)` intervals and `O(n)` possible split points for each interval.

- Time: `O(n^3)`.
- Space: `O(n^2)`.

## Classic validation example
For matrices with dimensions:

`10 20 30 40 30`

we have:

`A1 = 10x20`
`A2 = 20x30`
`A3 = 30x40`
`A4 = 40x30`

The optimal parenthesization is:

`(((A1 x A2) x A3) x A4)`

with minimum cost:

`30000` scalar multiplications.

## C compilation
```bash
gcc q7.c -o q7
./q7
```

Example input:
```text
4
10 20 30 40 30
```
