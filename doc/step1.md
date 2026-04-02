# Step 1: The First Spark (Single Ball)

## Goal
The goal of this version is to establish the basic application structure, initialize a graphical window, and create a simple simulation of a single bouncing particle on the screen. It serves as the foundation for future complexity.

## Design
The design focuses on setting up the core **Simulation Loop**:
1. **Initialization**: Create an 800x480 window and set a target FPS (60). Seed the random number generator to give the particle a random initial velocity.
2. **Input**: None for this stage.
3. **Update**: Modify the particle's position based on its velocity and the elapsed frame time (`dt`).
4. **Draw**: Clear the background to black, render the particle as a white circle, and display the current FPS.

## Algorithms
### The Bouncing Algorithm
To simulate a realistic bounce, we check if the particle's position (accounting for its radius) exceeds the screen boundaries.
- **Horizontal**: If `x + radius >= ScreenWidth` or `x - radius <= 0`, then `velocity.x = -velocity.x`.
- **Vertical**: If `y + radius >= ScreenHeight` or `y - radius <= 0`, then `velocity.y = -velocity.y`.

## Theories
### Kinematics
The movement of the particle is based on basic kinematics, where position is updated over time based on velocity:
$$Position_{new} = Position_{old} + Velocity \times \Delta t$$
Using the delta time ($\Delta t$) ensures that the movement speed is frame-rate independent.

## Learning Targets
- **Raylib Basics**: Using `InitWindow`, `CloseWindow`, `WindowShouldClose`, `BeginDrawing`, `EndDrawing`, and `ClearBackground`.
- **Time Management**: Using `GetFrameTime()` for frame-rate independent movement.
- **Basic Rendering**: Drawing primitive shapes (`DrawCircleV`) and text (`DrawFPS`).
- **C++ Standard Library**: Using `<cstdlib>` and `<ctime>` for generating random initial velocities.
- **Build System**: Using a basic `Makefile` to compile and link C++ programs with external libraries (`-lraylib`, `-lX11`).
