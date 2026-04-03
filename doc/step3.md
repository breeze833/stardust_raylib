# Step 3: The Nexus (Inter-particle Connections)

## Goal
The goal of this version is to move beyond independent movement and establish relationships between particles. By calculating the distance between every pair of particles, the program draws dynamic connection lines that fade based on proximity, creating a complex, web-like visual structure.

## Design
This stage introduces spatial awareness and enhanced visual depth:
1.  **Relational Parameters**: A `connectionThreshold` (100.0f) is added to the global `config` struct to define the maximum distance for a connection.
2.  **Pairwise Comparison**: A nested loop mechanism compares every particle against every other unique particle in the collection.
3.  **Proximity-Based Rendering**: 
    * The `draw_connection()` function calculates the distance between two particles using `Vector2Distance`.
    * If the distance is within the threshold, a line is drawn between them using `DrawLineV`.
    * **Alpha Modulation**: The line's color (Yellow) is dynamically faded using `Fade()`. The opacity decreases linearly as distance increases, reaching zero at the threshold.
4.  **Visual Hierarchy**: Particles are drawn first, followed by the connection lines, layered on a black background with an FPS counter.

## Algorithms
### The $O(N^2)$ Pairwise Distance Check
To find every possible connection, the program uses a nested loop in the drawing phase. To avoid redundant checks (e.g., checking both A-B and B-A) and self-comparison (A-A), an optimized indexing strategy is used:
1.  **Outer Loop**: Iterates from index $i = 0$ to $N-2$.
2.  **Inner Loop**: Iterates from index $j = i + 1$ to $N-1$.
3.  **Distance Calculation**: 
    $$d = \sqrt{(x_j - x_i)^2 + (y_j - y_i)^2}$$
    In the code, this is handled by `Vector2Distance(p1.position, p2.position)`.
4.  **Linear Opacity Calculation**:
    $$\text{opacity} = 1.0 - \left( \frac{d}{\text{threshold}} \right)$$

## Theories
### Quadratic Complexity ($O(N^2)$)
* **Computational Cost**: Unlike the update step which is linear ($O(N)$), the connection logic is quadratic ($O(N^2)$). The number of checks is exactly $\frac{N(N-1)}{2}$. For 50 particles, this results in 1,225 checks per frame.
* **Performance Wall**: As $N$ grows, the processing time increases exponentially. This makes the $O(N^2)$ check the primary performance bottleneck in generative simulations.
* **Alpha Blending and Fading**: Using `Fade()` demonstrates how transparency can be used to represent "strength" or "influence" in a relational system, a common technique in data visualization and generative art.

## Learning Targets
* **Nested Loops for Combinations**: Implementing the $i/j$ loop pattern to iterate over unique pairs in a collection.
* **Spatial Mathematics**: Using the `raymath.h` library for vector operations like `Vector2Distance`.
* **Dynamic Visuals**: Using `Fade()` to map a physical property (distance) to a visual property (opacity).
* **Code Refactoring**: Moving specific rendering logic into a dedicated function (`draw_connection`) to keep the main loop manageable.
* **Algorithmic Awareness**: Recognizing the difference between linear and quadratic complexity and its impact on real-time performance.
