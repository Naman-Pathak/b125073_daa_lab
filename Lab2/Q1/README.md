# Data Structures & Time Complexity Analysis in C

A C implementation of **arrays, singly linked lists, and doubly linked lists**, with both **sorted and unsorted** variants.

This project demonstrates common data-structure operations and compares their **time complexities** to understand the trade-offs between different data structures.

---

## Features

The project implements the following data structures:

* Unsorted Array
* Sorted Array
* Unsorted Singly Linked List (SLL)
* Sorted Singly Linked List (SLL)
* Unsorted Doubly Linked List (DLL)
* Sorted Doubly Linked List (DLL)

The following operations are implemented:

* Search
* Insert
* Delete
* Find Minimum
* Find Maximum
* Find Predecessor
* Find Successor

It also generates an **SVG graph** showing the growth of:

* `O(1)`
* `O(log n)`
* `O(n)`

---

## Data Structures

### 1. Unsorted Array

An array whose elements are not maintained in any particular order.

* Searching requires linear traversal.
* Insertion is performed at the end.
* Deletion replaces the deleted element with the last element.

### 2. Sorted Array

An array whose elements are maintained in ascending order.

* Binary search can be used for searching.
* Insertion requires shifting elements.
* Deletion requires shifting elements to fill the gap.

### 3. Unsorted Singly Linked List

Each node contains:

```c
value
next
```

Insertion is performed at the beginning of the list.

### 4. Sorted Singly Linked List

Nodes are maintained in ascending order.

Insertion requires finding the correct position before linking the new node.

### 5. Unsorted Doubly Linked List

Each node contains:

```c
value
previous
next
```

The additional `previous` pointer allows traversal in both directions and makes deletion of a known node efficient.

### 6. Sorted Doubly Linked List

A doubly linked list that maintains ascending order.

The list maintains both:

```text
first
last
```

This allows minimum and maximum values to be accessed directly.

---

# Time Complexity

The important part for understanding and viva preparation is the following comparison table:

| Data Structure |   Search | Insert | Delete |  Min |  Max |
| -------------- | -------: | -----: | -----: | ---: | ---: |
| Unsorted Array |     O(n) |  O(1)* |  O(1)* | O(n) | O(n) |
| Sorted Array   | O(log n) |   O(n) |   O(n) | O(1) | O(1) |
| SLL Unsorted   |     O(n) |  O(1)* |   O(n) | O(n) | O(n) |
| SLL Sorted     |     O(n) |   O(n) |   O(n) | O(1) | O(n) |
| DLL Unsorted   |     O(n) |  O(1)* | O(1)** | O(n) | O(n) |
| DLL Sorted     |     O(n) |   O(n) | O(1)** | O(1) | O(1) |

### Important Notes

`*` **O(1) insertion/deletion assumes the required position or operation can be performed directly.**

For the unsorted array, deletion is O(1) because the implementation replaces the deleted element with the last element instead of shifting all remaining elements.

For the unsorted SLL, insertion is O(1) because insertion is performed at the head.

`**` **O(1) deletion for a DLL assumes that a pointer to the target node is already available.**

If the node first has to be searched using its value:

```text
Search = O(n)
Delete = O(1)

Total = O(n)
```

---

# Why Is Sorted Array Search O(log n)?

A sorted array supports **binary search**.

Instead of checking every element one by one, binary search checks the middle element and eliminates half of the remaining search space after every comparison.

For example:

```text
[1, 5, 10, 13, 20, 25, 30, 40]

                 ↓
              Check 13

Target > 13
Discard left half

[20, 25, 30, 40]
       ↓
    Continue
```

Therefore:

```text
O(n) → Linear Search
O(log n) → Binary Search
```

However, a sorted linked list still has **O(n) search** because linked lists do not provide direct/random access to the middle element.

---

# Why Is Sorted Array Insertion O(n)?

Although searching for the correct position can be done efficiently, the elements after that position may need to be shifted.

For example:

```text
Before:

[10, 20, 30, 40, 50]

Insert 25:

[10, 20, 25, 30, 40, 50]
          ↑
       inserted
```

`30`, `40`, and `50` have to be shifted.

Therefore:

```text
Sorted Array Insert = O(n)
```

This is an important trade-off:

```text
Fast Search
    ↓
O(log n)

but

Expensive Insert/Delete
    ↓
O(n)
```

---

# Why Are Sorted Linked Lists Still O(n) for Search?

Sorting alone does **not** make a data structure capable of binary search.

A sorted array can directly access:

```text
arr[middle]
```

in `O(1)`.

A linked list cannot directly access its middle node.

It has to follow:

```text
head
 ↓
node
 ↓
node
 ↓
node
 ↓
...
```

Therefore, even though the list is sorted:

```text
Sorted SLL Search = O(n)
Sorted DLL Search = O(n)
```

---

# Why Is DLL Deletion O(1)?

If we already have a pointer to the node that needs to be deleted, its neighboring nodes can be connected directly.

For example:

```text
A <-> B <-> C
```

Delete `B`:

```text
A <--------> C
```

Only the neighboring pointers need to be updated.

Therefore:

```text
DLL Delete = O(1)
```

when the target node is already known.

If we first need to search for `B`:

```text
Search → O(n)
Delete → O(1)

Overall → O(n)
```

---

# Complexity Graph

The program generates an SVG graph named:

```text
complexity_graph.svg
```

The graph visually compares:

```text
O(1)
O(log n)
O(n)
```

### Graph Axes

```text
X-axis → Number of Elements (N)
Y-axis → Time Taken
```

The graph contains:

* X and Y axes
* Grid lines
* Complexity curves
* Labels
* Legend
* Data-structure performance summary

---

# Project Structure

```text
.
├── main.c
├── complexity_graph.svg
└── README.md
```

### `main.c`

Contains all data structures, operations, complexity graph generation, and the `main()` function.

### `complexity_graph.svg`

Generated automatically when the program is executed.

### `README.md`

Project documentation and complexity analysis.

---

# Requirements

You need a C compiler such as:

* GCC
* Clang
* MinGW

The program uses the following standard C libraries:

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
```

---

# Compilation

Using GCC:

```bash
gcc main.c -o data_structures -lm
```

The `-lm` flag links the mathematical library because the program uses the `log()` function while generating the complexity graph.

---

# Running the Program

### Linux / macOS

```bash
./data_structures
```

### Windows / MinGW

```bash
data_structures.exe
```

---

# Expected Output

The program creates a sorted doubly linked list and inserts the following values:

```text
10
5
202
101
52
201
13
54
1
```

Because the list is sorted, the values are maintained in ascending order.

The program then displays:

```text
Minimum: 1
Maximum: 202
```

It also generates:

```text
complexity_graph.svg
```

---

# Concepts Demonstrated

This project demonstrates several important Data Structures and Algorithms concepts:

### Arrays

* Contiguous memory
* Index-based access
* Linear search
* Binary search
* Element shifting

### Singly Linked Lists

* Dynamic memory allocation
* Nodes
* Pointers
* Head insertion
* Sequential traversal

### Doubly Linked Lists

* `previous` pointer
* `next` pointer
* Bidirectional traversal
* Efficient deletion of known nodes

### Sorted Data Structures

* Maintaining ascending order
* Faster searching in arrays
* Cost of maintaining order during insertion

### Asymptotic Analysis

* `O(1)` — Constant
* `O(log n)` — Logarithmic
* `O(n)` — Linear

---

# Points to be noted

The project demonstrates that **the best data structure depends on the operations that need to be performed most frequently.**

There is always a trade-off.

```text
Unsorted Array
→ Fast insertion
→ Slow search

Sorted Array
→ Fast search
→ Expensive insertion/deletion

Unsorted SLL
→ Fast head insertion
→ Slow search

Sorted SLL
→ Maintains order
→ Search is still O(n)

Unsorted DLL
→ Fast insertion
→ Fast deletion of known nodes

Sorted DLL
→ Fast min/max
→ Fast predecessor/successor
→ Search and insertion remain O(n)
```

The most important principle is:

> **Choosing a data structure is about choosing which operations you want to make efficient.**

---

# Author

**Naman**

B.Tech Computer Science & Engineering
