# DAA Lab-07 — Dynamic Programming Solutions

This package contains C implementations and individual detailed `README.md` files for all questions in the uploaded DAA Lab-07 sheet.

## Included questions

| Folder | Topic | Main technique |
|---|---|---|
| `Q1_Coin_Triangle` | Invert the coin triangle | Closed-form geometry + prefix DP validation |
| `Q2_Super_Egg` | Super egg testing | Dynamic programming |
| `Q3_Reves_Puzzle` | Reve's four-peg puzzle | Frame-Stewart dynamic programming |
| `Q4_Security_Switches` | Security switches | Dynamic-programming recurrence |
| `Q5_Moving_Target` | Hitting a moving target | Belief-state DP validation + constructive schedule |
| `Q6_Best_Time_Alive` | Maximum scientists alive | Event sweep + prefix DP |
| `Q7_Matrix_Chain_Multiplication` | MCM | Dynamic programming |

## Source basis
The folder follows the exact seven tasks in the uploaded lab sheet. Questions 1–6 appear on pages 1–2 and Q7 is the MCM task on page 2.

## General note about “using DP”
Not every puzzle is naturally a large table-DP problem. Where a direct mathematical or constructive solution is the natural method, the implementation includes a DP/prefix-state validation layer rather than forcing an artificial recurrence. The individual READMEs explain this distinction.

## Compilation
Each folder contains one `.c` file and one `README.md`.

Example:
```bash
cd Q2_Super_Egg
gcc q2.c -o q2
./q2
```

## Recommended order for lab preparation
Q2 → Q7 → Q3 → Q4 → Q6 → Q5 → Q1

This order moves from standard textbook DP to the more puzzle-oriented state/constructive problems.
