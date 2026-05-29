# Ai Pathfinding - Random Search

A C++ and Raylib implementation of a random walk pathfinding algorithm on a 2D grid.

## Overview
This project visualizes a naive random search algorithm attempting to find a path from a Start node (`S`, Green) to an End node (`E`, Blue) across a procedurally generated obstacle grid. The grid is constructed using standard C++ vectors, and rendering is handled by the Raylib framework.

<img src="Animation.gif" height="500">

## Mechanics
- **Grid Generation:** The map is populated with random obstacles (black squares) based on a defined percentage upon initialization or restart.
- **Random Search:** The AI randomly selects an unvisited neighboring tile. If it hits a dead end (no unvisited neighbors), the current path fails, fades the failed attempt visually, and the search restarts from the beginning.
- **Path Success:** If the End node is reached, the final successful path is highlighted in gold and numbered sequentially.

## Controls
- `R`: Regenerate the grid and restart the simulation.

## Technical Structure
- **Node Management:** Grid cells are managed via a custom `Node` struct storing position, blockage state, and display properties.
- **Path Tracking:** Standard library `std::vector` is utilized to track both `currentPath` and `currentVisited` nodes to prevent immediate backtracking during a search cycle. 
