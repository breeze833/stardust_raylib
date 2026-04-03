# Step 7: The Architect (Refactoring and State Management)

## Goal
The goal of this final architectural step is to apply the principle of **Encapsulation** and transition from a scripting-style procedural approach to a professional, architect-style object-oriented design. By moving the loose variables and fragmented logic into a dedicated `StardustApp` class, the code becomes more modular, maintainable, and aligned with industry standards for simulation and game development.

## Design
This stage focuses on "Cleaning the House" to improve code organization while maintaining the visual behavior of the simulation:
1.  **Application Wrapper**: The `StardustApp` class acts as the central hub, owning all simulation data, including the particle collection, attractors, and configuration parameters.
2.  **Lifetime Methods**: Standardized methods manage the application lifecycle:
    * `init()`: Initializes the Raylib window, seeds the random generator, and populates the particle system.
    * `run()`: Contains the high-level execution loop.
    * `update()`: Orchestrates physics calculations and attractor logic.
    * `draw()`: Handles all rendering operations, including the persistence effect and particle/connection drawing.
    * `cleanup()`: Safely closes resources and the window.
3.  **Encapsulation of State**: Internal variables such as `particles`, `config`, and the attractor pointers (`mouseGravity`, `autoGravity`) are moved to private member scope to prevent accidental external modification.
4.  **The Clean `main()`**: The entry point in `main.cpp` is reduced to a minimal script that instantiates the app and orchestrates its high-level lifecycle.

## Algorithms
### The Member-Based Loop
The core simulation loop is refactored into a member function. This removes the need for "Prop Drilling" (passing multiple arguments through deep function chains) because all necessary state is accessible via the `this` pointer.

```cpp
// Logic flow in StardustApp::run()
while (!WindowShouldClose()) {
    update();
    draw();
}
```

### Resource Management
The `StardustApp` class manages its own dependencies. The attractors are instantiated in the constructor and released in the destructor, following basic memory management principles.

## Theories
### Encapsulation and Information Hiding
* **Data Privacy**: By using access specifiers (`private`), the application protects its internal state (`StardustAppConf`, `vector<Particle>`), exposing only a clean public interface (`init`, `run`, `cleanup`).
* **Separation of Concerns**: Infrastructure (windowing), logic (physics), and entry-point orchestration are now physically and logically separated into different files and methods.

### Refactoring and Technical Debt
* **Strategic Refactoring**: This step demonstrates that software quality is not just about features, but about the *structure* of the code. Refactoring "pays down" the technical debt accumulated during the rapid iterations of Steps 1 through 6.
* **Maintainability**: A modular architecture allows for easier future extensions (e.g., adding more particle types or new rendering modes) without breaking existing functionality.

## Learning Targets
* **Object-Oriented Architecture**: Building a central manager class to wrap simulation state.
* **C++ Class Design**: Mastering the use of headers (`StardustApp.h`), implementation files (`StardustApp.cpp`), and access specifiers.
* **Life-cycle Management**: Implementing consistent initialization and cleanup routines.
* **Build System Scaling**: Updating the `Makefile` to handle multiple source files and complex dependencies.
* **The "Clean Main" Philosophy**: Understanding that a mature software project should have a minimal and expressive entry point.
