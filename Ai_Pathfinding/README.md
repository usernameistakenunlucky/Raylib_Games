# Ai Pathfinding

A C++ and Raylib implementation visualizing various pathfinding algorithms on a 2D grid.

## Visualizations

### Breadth-First Search (BFS)
<img src="bfsAnimation.gif" height="300">

### Depth-First Search (DFS)
<img src="dfsAnimation.gif" height="300">

### Random Search
<img src="randomAnimation.gif" height="300">

## Mechanics
* **Grid Generation:** Generates a 20x20 grid where 25% of the nodes are randomly designated as solid black obstacles. 
* **Breadth-First Search (BFS):** Layer-by-layer exploration using a FIFO queue. Explored nodes animate in light blue, and the final shortest path is traced sequentially in gold.
* **Depth-First Search (DFS):** Deep branch exploration using a LIFO stack. Explored nodes animate in purple, tracing the discovered path in gold once the end node is hit.
* **Random Search:** A naive random walk that selects unvisited neighbors, resetting from the start node if it reaches a dead end.

## Controls
* `B`: Execute Breadth-First Search.
* `D`: Execute Depth-First Search.
* `R`: Execute Random Search.
* `X`: Regenerate map obstacles and randomize Start (S) and End (E) positions.

## Technical Structure
* **Node (`Node.h`):** Represents an individual tile grid cell. Manages traversal state variables (visited, parent pointer, step count) and handles node-scaling render animations.
* **State Machine (`Ai.h` / `Ai.cpp`):** Manages the core game loop, input polling, grid generation logic, and steps through the active search algorithm state.