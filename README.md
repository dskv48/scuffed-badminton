# The Scuffed Badminton Problem

This repository contains the official paper, algorithmic code, and simulation scripts for **"The Scuffed Badminton Problem: Finding the Expected Hitting Time for the (1,n) State in a Simplification-Based Scoring System"**, accepted for publication in *Parabola* (Volume 62, Issue 2, August 2026).

📄 **[Read the full paper here (PDF)](./The_Scuffed_Badminton_Problem__Finding_the_Expected_Hitting_Time_for_the__1_n__State.pdf)**

## The Problem
"Scuffed Badminton" models a two-player game (which can be mapped as a random walk on a directed graph) where reaching a score of `(a, b)` immediately "simplifies" down to `(a/gcd(a,b), b/gcd(a,b))`. 

This code calculates the expected number of rallies ($E_n$) to reach a target score state of `(1,n)` from a starting state of `(1,1)`, assuming both players are equally skilled.

## Repository Contents

### 1. The Mathematical Model
* `The_Scuffed_Badminton_Problem__Finding_the_Expected_Hitting_Time_for_the__1_n__State.pdf`: The complete mathematical paper. It details the proofs, the Markov chain methodology used to derive exact values for $n \le 11$, and the analysis of the state space.

### 2. Algorithmic Implementations
* **`markov_expected_value.cpp`**: A C++ algorithm that recursively computes the exact expected hitting times for $n \le 11$. It generates the state transitions of the Markov Chain and calculates the precise fractional and decimal expected values.
* **`dfs_escape_test.cpp`**: A C++ Depth-First Search (DFS) traversal. This script demonstrates the memory boundaries of the state space and mathematically proves why algorithmic calculation becomes computationally unfeasible for $n \ge 12$ due to escaping states.
* **`monte_carlo_sim.py`**: A multi-threaded Python Monte Carlo simulator (co-developed with Mingzhou Lee). It is used to estimate $E_n$ for $n \ge 12$ across millions of trials, successfully validating the C++ algorithm's accuracy to within 0.2%.

## Running the Code
**C++ Scripts:**
Compile using standard `g++`:
```bash
g++ -o markov_calc markov_expected_value.cpp
./markov_calc
