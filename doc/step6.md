# Step 6: The Ghost in the Machine (Polymorphism and Autonomy)

## Goal
The goal of this final version is to transition the project from a purely interactive tool to an **autonomous art installation**. By implementing **Runtime Polymorphism**, the program becomes capable of self-governing: it switches between manual user control (Mouse) and a self-moving "Ghost" mode (Algorithm). This ensures the simulation remains visually captivating even without continuous user input.

## Design
This stage focuses on high-level software architecture and autonomous behavior:
1.  **Abstract Interface**: A base class `Attractor` defines a common interface for anything that can generate a gravity point.
2.  **Concrete Implementations**:
    * **`MouseAttractor`**: Retrieves coordinates based on mouse click events (`IsMouseButtonPressed`).
    * **`AutoAttractor`**: Generates coordinates based on a mathematical Lissajous curve.
3.  **Autonomous Triggering**: A `autoGravityInterval` (15.0s) is added to the `config` struct. The program tracks the time since the last attraction event. If no mouse click is detected for the duration of the interval, the `AutoAttractor` is automatically activated to provide a gravity pulse.
4.  **Decoupled Physics**: The `update_particle` function now accepts a `std::optional<Vector2>` provided by the current active `Attractor`, making the physics logic agnostic to the source of the force.

## Algorithms
### The Lissajous Curve
To create smooth, non-repetitive movement for the `AutoAttractor`, the program uses **Lissajous Curves**. This allows the "Ghost" to weave across the screen in complex loops:
* **Horizontal Position**: $x(t) = A \cdot \sin(a \cdot t + \delta) + A$
* **Vertical Position**: $y(t) = B \cdot \sin(b \cdot t) + B$
* Parameters in the code ($a=0.7, b=1.1, \delta=\pi/2$) ensure a path that takes a long time to repeat, creating a natural feel.

### Runtime Polymorphism and Switching Logic
The simulation manages the two attractor types and switches based on user activity:
1.  **Interface Usage**: The main loop uses a pointer (`Attractor *attractor`) to refer to either the mouse or the auto attractor.
2.  **State Logic**:
    * If `mouseGravity.getPosition()` has a value (mouse clicked), the timer `lastAttract` is reset.
    * If no value is present and the `curTime > lastAttract + autoGravityInterval`, the `autoGravity` attractor is selected and triggered.
3.  **Virtual Dispatch**: The C++ **vtable** ensures the correct `getPosition()` and `update()` methods are called at runtime.

## Theories
### Object-Oriented Design: Polymorphism
* **Interface vs. Implementation**: Polymorphism allows the definition of *what* an object should do separately from *how* it does it.
* **Separation of Concerns**: The particle update logic only cares about *where* the gravity is, not *why* it is there.
* **Software Adaptability**: The system is designed to handle different environments, such as an interactive desktop app or a passive wall projection, using the same codebase.

### The "Installation" Mindset
* **Passive Engagement**: In a projection setting, the system must provide a continuous, evolving performance. The `AutoAttractor` ensures the "canvas" remains dynamic even when no viewers are interacting with it.
* **Aesthetics of Autonomous Motion**: The mathematical curves combined with the "Afterglow" effect from Step 5 turn the screen into an evolving light painting, emphasizing the fluid, organic nature of the generative system.

## Learning Targets
* **C++ Inheritance**: Defining the `Attractor` base class and derived classes.
* **Virtual Functions**: Using `virtual` and `override` for runtime method binding.
* **Abstract Classes**: Implementing pure virtual functions (`= 0`) to define interfaces.
* **Smart Interaction Logic**: Implementing time-based state switching to create autonomous behavior.
* **Mathematical Pathfinding**: Applying trigonometry and Lissajous curves for procedural animation.
* **Modular Code Organization**: Splitting classes into header (`.h`) and implementation (`.cpp`) files and updating the `Makefile` accordingly.
