# Topology Module Documentation

## Purpose

The `Topology` module provides core algorithms for constructing and analyzing the connectivity of a **Topological Space**. It works on two main representations:

1. **Open Sets Representation** – The topology is stored as a collection of open sets, each containing indices of points.
2. **Adjacency Representation** – The topology is stored as an adjacency list, representing direct connections between points.

## Core Data Structures

* **Points (`std::vector<Point>`)**
  Stores optional coordinates `(x, y, z)` of each point in the space.

* **Open Sets (`std::vector<std::set<int>>`)**
  Each set represents a collection of points forming an open set in the topology.

* **Adjacency List (`std::vector<std::vector<int>>`)**
  Stores neighbors for each point, describing graph connectivity.

## Algorithms

### 1. `buildAdjacencyFromOpenSets()`

**Goal:** Convert the topology from open set form to adjacency list form.
**Process:**

1. For every open set, connect every pair of points within it.
2. Store these connections in an intermediate `unordered_set` to avoid duplicates.
3. Convert the sets into adjacency vectors for final storage.

**Complexity:**

* Let `n` = number of points, `m` = total size of all open sets.
* Time: **O(m²)** in the worst case for large open sets.
* Space: **O(n + m)**.

### 2. `buildOpenSetsFromAdjacency()`

**Goal:** Reconstruct open sets from an adjacency list.
**Process:**

1. For each point `u`, create an open set containing:

   * The point itself.
   * All points in its adjacency list.
2. Store these sets in the `openSets` vector.

**Complexity:**

* Let `n` = number of points, `e` = number of edges.
* Time: **O(n + e)**.
* Space: **O(n + e)**.

## Notes

* **Data Integrity:**
  The two representations are interchangeable using the above functions. This allows flexibility for algorithms that prefer one form over the other.

* **Usage Pattern:**

  1. Define points and open sets.
  2. Build adjacency with `buildAdjacencyFromOpenSets()`.
  3. (Optional) Rebuild open sets with `buildOpenSetsFromAdjacency()` if the graph changes.

## Open Sets → Adjacency List Diagram

Suppose we have 3 points: `0`, `1`, `2`
And the open sets:

```
OpenSets = {
    {0, 1},
    {1, 2},
    {0, 2}
}
```

**Step 1: Draw Open Sets Connections**

```
Open Set {0, 1} → connects 0 ↔ 1
Open Set {1, 2} → connects 1 ↔ 2
Open Set {0, 2} → connects 0 ↔ 2
```

**Step 2: Build Adjacency List**

```
Adjacency:
0: 1, 2
1: 0, 2
2: 0, 1
```

**Step 3: Visual Representation (Graph)**

```
    0
   / \
  1---2
```

* Each point is a node.
* An edge exists if two points appear together in an open set.
* This adjacency graph is automatically built by `buildAdjacencyFromOpenSets()`.
* Rebuilding open sets from adjacency recreates all sets containing each point and its neighbors.


## Topology Class and Functions

The `Topology` class inherits from `TopologicalSpace` and provides higher-level topological operations and analysis.

### Constructor

`Topology(int numPoints, const OpenSetCollection& openSets)`

* Initializes `points` with `numPoints`.
* Stores the provided `openSets`.

### Functions

#### `neighborhood(int p)`

* **Goal:** Return all neighbors of point `p`.
* **Algorithm:** Ensures adjacency is built from open sets, then returns `adjacency[p]`.
* **Complexity:** O(degree of `p`)

#### `closure(const std::set<int>& A)`

* **Goal:** Compute the closure of a subset of points `A`.
* **Algorithm:** Ensures adjacency is built, then adds all points connected to any point in `A`.
* **Complexity:** O(|A| × max degree)

#### `interior(const std::set<int>& A)`

* **Goal:** Compute the interior of a subset `A`.
* **Algorithm:** For each point in `A`, check if all its neighbors are in `A`. If yes, include it in the interior.
* **Complexity:** O(|A| × max degree)

#### `isConnected()`

* **Goal:** Determine if the space is connected.
* **Algorithm:** Performs DFS starting from point 0. If all points are visited, the space is connected.
* **Complexity:** O(n + e), where n = number of points, e = number of edges

### Private Helper Functions

* `ensureAdjacency()`: Builds adjacency from open sets if not already done.
* `dfs(int v, std::set<int>& visited)`: Depth-first search for connectivity checks.


## nothing is tested yet 
## the documentation was done by open AI's gpt-5 LLM