# Q6 — The Best Time to Be Alive

## Problem
Given the birth and death years of prominent scientists, find a year when the largest number of them were alive.

The input index is alphabetically sorted, but alphabetical order does not help with the numerical overlap calculation. We only need the birth/death years.

Special rule from the lab:

> If one person died in the same year another person was born, the death happens first.

Therefore, for equal years, death events must be processed before birth events.

## Event transformation
For every scientist `(birth, death)`, create two events:

- `(birth, +1)`
- `(death, -1)`

After sorting by `(year, event type)`, scan the events from left to right.

## Dynamic-programming / prefix recurrence
Let `active[i]` be the number of scientists alive after processing event `i`.

Then:

`active[0] = delta[0]`

`active[i] = active[i-1] + delta[i]`

This is a prefix DP: every state depends only on the previous state.

Whenever `active[i]` becomes larger than the best value seen so far, update the answer year.

## Why death-before-birth matters
Suppose scientist A dies in 1900 and scientist B is born in 1900. Under the lab rule, A's `-1` event is processed before B's `+1` event. Thus they are never counted as simultaneously alive.

## Algorithm
1. Read all birth/death pairs.
2. Convert each pair to one birth event `(+1)` and one death event `(-1)`.
3. Sort events by year.
4. For equal years, put deaths before births.
5. Scan the sorted list, maintaining the current number alive.
6. Record the year when a new maximum is reached.

## Complexity
With `n` scientists there are `2n` events.

- Sorting: `O(n log n)`.
- DP/prefix scan: `O(n)`.
- Total: `O(n log n)`.
- Extra space: `O(n)`.

## C compilation
```bash
gcc q6.c -o q6
./q6
```

Example input:
```text
5
1500 1560
1510 1580
1540 1600
1550 1590
1570 1620
```

The program reports a year having the maximum number alive.
