# Q5 — Hitting a Moving Target

## Problem
There are `n > 1` hiding spots in a line. The shooter can shoot any one spot per shot. The target is invisible, and between two consecutive shots it moves exactly one step to an adjacent spot.

We must design a strategy that guarantees a hit, or prove that none exists.

## State representation: DP over possible positions
Because the target is invisible, we do not know its exact position. Instead, maintain a set of all positions where it **could** be.

Let:

`possible[t][p] = true`

mean that immediately before shot `t`, the target may be at position `p`.

For a shot at position `s`:

1. Any target at `s` is hit, so remove `s` from the possible set.
2. If the target survives, it moves one step left or right before the next shot.
3. The next DP state is obtained by propagating every surviving position to its adjacent positions.

If the possible set ever becomes empty immediately after a shot, the strategy is guaranteed to have hit the target.

## Constructive guaranteed strategy
A simple family of strategies is:

### n = 2
Shoot:

`1, 1`

### n is odd
Shoot:

`2, 3, ..., n-1, 2, 3, ..., n-1`

### n is even
Shoot:

`2, 3, ..., n-1, n-1, n-2, ..., 2`

The idea is to sweep through the interior positions. Since the target must move every time the shooter misses, repeatedly sweeping the line prevents the target from staying forever on one side of the shooter.

## Example: n = 5
Shots:

`2, 3, 4, 2, 3, 4`

Starting with all five positions possible, the DP update repeatedly removes positions shot at and moves all remaining possibilities by one step. After the final shot, no possible target position remains, so the sequence guarantees a hit.

## Number of shots
- For `n = 2`: 2 shots.
- For `n >= 3`: `2(n-2)` shots.

This is a constructive guarantee; the lab question does not require proving that this particular schedule is the shortest possible schedule.

## Complexity
For the validating DP:

- Number of shots: `O(n)`.
- Each update scans `O(n)` positions.
- Time: `O(n^2)`.
- Space: `O(n)`.

The schedule itself is generated in `O(n)` time.

## C compilation
```bash
gcc q5.c -o q5
./q5
```

Try values such as `n = 3, 4, 5, 6` and observe that the validator prints `Guaranteed hit: YES`.
