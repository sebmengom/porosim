# Porosim
## What is Porosim?
Porosim is a Percolator simulator that uses a Disjoint Set Algorithm as its engine. 
## DSU Explanation
A Disjoint Set Algorithm works by having multiple sets of numbers that are "owned" by a root, meaning all of the sets have a main root. To connect a set with another one, the algorithm is set up to have the smaller set join the largest set, making the root of the biggest set, is now root of both sets. This makes it easier to find connections among indexes, as to find a connection, you will only need to see if the root of a 2 different indexes are the same, if not, you could either add them to the set, or ignore, as is the case in the percolator.
### How does the algorithm work? 
It is pretty simple actually, in this project I am only using a 1D array, each value in the array is set as its own owner at the beggining, meaning that arr[n] = n, however what DSU does is that it changes the value inside of the index to point at the "Boss" of the index, a bit weird to explain but here is the explanation with code:
```cpp
int arr[5] {0,1,2,3,4};
arr[2] = 1; /// 1 is now the root for index at 2, whenever you access index 2, you will be directed to 1.
```
That is just a pretty vague explanation on how the algorithm works, I will continue to explain how this same algorithm is implemented inside of Porosim.
# How DSU works inside of Porosim
Now that I wrote a brief explanation of what DSU is and how it works, I want to explain how I applied this algorithm inside of Porosim.
## DSU class
The DSU class inside of dsu.h, contains different methods and private variables.
### The variables
The class contains a parent array, initialized at N size filled with numbers from 0 to N-1.
A vector that keeps track of the size of the set owned by each root.
### Methods 
- findSet:
The find set method is pretty simple and efficient, it will check if the value at index N = N, if it does NOT, it will call itself again in a recursive way until the value at N = N, when this scenario happens you will find the root, and set all of the other previous "found values" to the root value.
Example:
```cpp
int arr[5] {0, 0, 2, 1, 3};
findSet(4)
```
This will check the value inside arr[4], it will be 3, is 3 == 4? No, so it will visit arr[3], this will be 1, is 1 == 3? No, you visit arr[1], you will find 0, is 0 == 1? No, you go to arr[0], here 0 == 0. You have found the root. Every previous value visited that wasn't already the root (arr[4] and arr[3]) will now be changed to 0. arr[1] was already 0, so it stays the same.
```cpp
int arr[5] {0, 0, 2, 0, 0};
```
- unionSets:
This method takes 2 (A, B) indices, and uses the findSet method to find both of their roots. If the roots are not the same, it checks if the size of A's set is smaller than the size of B's set — if so, it swaps which variable (A or B) refers to the bigger root. Then it makes the parent of the smaller root equal to the bigger root, and increments the bigger root's size (adding the smaller root's size).
- connected:
This simply checks if the root of A and the root of B are the same, and returns true or false (a bool) — not 1 or 0.
## percolator class
The percolator class builds on top of the DSU class to run the actual percolation simulation.
### Constructor
The array size is n*n+2 instead of just n*n, because 2 extra indices are added to represent two virtual nodes: top and bottom. top is index n*n, and bottom is index n*n+1. These aren't real grid cells — they exist so percolation can be checked with a single connected() call: if top and bottom ever end up in the same set, the grid has percolated.
### openGate
First, row and col are converted into a 1D index with `int i{row * n + col};`, and `gateStatus[i]` is set to 1, marking that cell as open.

Then it checks each of the four possible neighbors (up, down, left, right). Before doing a union with a neighbor, it checks `gateStatus[nb] == 1` — this confirms the neighbor is actually open. Without this check, openGate would union with every neighboring cell regardless of whether it's open, which doesn't make sense: closed cells shouldn't be connected to anything.

The other 2 checks (row==0 and row==n-1) union directly with top/bottom, with no gateStatus check. That's not optional, it's because top and bottom aren't real cells. gateStatus only has n*n entries (indices 0 to n*n-1), and top (n*n) and bottom (n*n+1) fall outside that range. There's no state to check for a virtual node, so the check simply doesn't apply there.
### isOpen
Converts row/col into the 1D index the same way openGate does, and returns whether gateStatus[i] is 1.
### percolates
Just returns arr.connected(top, bottom). If the two virtual nodes ended up in the same set, the grid percolated. No need to check every top-row cell against every bottom-row cell individually.
## Roadmap
### Next: Monte Carlo validation
Generate random cell openings using `<random>`, run hundreds of trials per grid size (10, 50, 100...), track the fraction of open cells at the moment each trial percolates, and average across trials. Compare the result against the theoretical site percolation threshold (~0.593) for a 2D square lattice.
### v2: pore-and-rock extension
Add a fluid injection point, route the fluid with BFS/DFS to trace the actual path it follows (not just detect connectivity), and benchmark performance across grid sizes using `<chrono>`.
