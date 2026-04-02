# Step 2: Emergence (Multiple Particles)

## Goal
The objective of this version is to transition from a single-particle system to a multi-particle simulation. This step focuses on data encapsulation, managing collections of objects using the C++ Standard Template Library (STL), and improving code modularity through functions and configuration structures.

## Design
This stage introduces several architectural improvements:
1.  **Configuration Encapsulation**: A global `config` struct centralizes simulation parameters like screen dimensions, particle count (50), and radius.
2.  **Particle Abstraction**: A `Particle` struct groups `position`, `velocity`, and `color` data.
3.  **Dynamic Collection**: Using `std::vector<Particle>` to manage the particle population.
4.  **Modularization**: Logic is broken down into helper functions:
    *   `random_particle()`: Handles the creation and randomized initialization of individual particles.
    *   `update_particle()`: Encapsulates the physics and boundary logic for a single particle.
5.  **Visual Variety**: Particles are initialized with random positions, velocities, and varying shades of gray.

## Algorithms
### Multi-Object Processing
The simulation loop is refactored to iterate through the particle collection:
1.  **Initialization**: A loop populates the `std::vector` by calling `random_particle()` $N$ times.
2.  **Update Phase**: A range-based for loop (`for (Particle& p : particles)`) passes each particle to `update_particle()` to modify its state based on $\Delta t$.
3.  **Draw Phase**: A separate loop iterates through the particles to render them using `DrawCircleV`.

## Theories
### Scalability and Abstraction
*   **Procedural Abstraction**: Moving logic into functions (`update_particle`) makes the main loop cleaner and the code easier to maintain as complexity grows.
*   **Linear Scaling**: The time complexity for both updating and drawing remains $O(N)$, where $N$ is the number of particles. As $N$ increases, the performance cost grows linearly.
*   **Data Locality**: Storing particles in a `std::vector` ensures they are contiguous in memory, which is generally more efficient for the CPU cache when iterating through the list.

## Learning Targets
*   **Structs and Types**: Using anonymous structs for configuration and `typedef struct` for data types.
*   **STL Vectors**: Managing dynamic arrays with `std::vector::push_back` and iterating with range-based for loops.
*   **Raylib Randomization**: Utilizing `SetRandomSeed` and `GetRandomValue` for deterministic or varied simulation starts.
*   **Function Decomposition**: Refactoring code into smaller, single-responsibility functions.
*   **Color Manipulation**: Creating `Color` objects with randomized RGB values to add visual depth.
*   **Configuration Management**: Using a dedicated structure to handle project-wide constants and settings.
