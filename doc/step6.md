# Step 6: The Ghost in the Machine (Polymorphism and Autonomy)

## Goal
The final version transitions the project from an interactive tool to an **autonomous art installation**. By implementing **Polymorphism**, the program becomes environmentally aware: it can switch between manual user control (Mouse) and a self-governing "Ghost" mode (Algorithm). This ensures the simulation remains captivating without requiring a mouse.

## Design
This stage focuses on high-level software architecture and autonomous behavior:
1.  **Abstract Interface**: Define a base class `Attractor` that establishes a common interface for anything that can "pull" the particles. 2.  **Concrete Implementations**:
    * **`MouseAttractor`**: Retrieves coordinates from the hardware mouse.
    * **`AutoAttractor`**: Generates coordinates using a mathematical path (Lissajous curve).
3.  **Environment Detection**: At startup, the program detects the presence of a mouse or checks for user input to decide which `Attractor` implementation to instantiate.
4.  **Decoupled Physics**: The `update_particle` function is refactored to accept a pointer to the `Attractor` interface, making the physics logic completely agnostic to the source of the force.

## Algorithms
### The Autonomous "Ghost" Path
To create an elegant, non-repetitive movement for the `AutoAttractor`, we use **Lissajous Curves**. This allows the "Ghost" to weave across the screen in complex loops:
* **Horizontal Position**: $x(t) = A \cdot \sin(a \cdot t + \delta) + \text{Center}_x$
* **Vertical Position**: $y(t) = B \cdot \sin(b \cdot t) + \text{Center}_y$
* By using non-integer ratios for $a$ and $b$ (e.g., $a=0.7, b=1.1$), the path takes a long time to repeat, creating a "living" feel.

### Runtime Polymorphism
The simulation uses a pointer to the base class to achieve dynamic binding:
1.  **Instantiation**: `Attractor* currentAttractor = new AutoAttractor();` (or `MouseAttractor`).
2.  **Execution**: During the update loop, the code calls `currentAttractor->GetPosition()`.
3.  **Resolution**: The C++ **vtable** ensures the correct version of the function is called at runtime based on the actual object type.


## Theories
### Object-Oriented Design: Polymorphism
* **Interface vs. Implementation**: Polymorphism allows us to define *what* an object should do (get a position) separately from *how* it does it (read hardware vs. calculate math).
* **Open-Closed Principle**: The system is "open for extension" (we could add a `KeyboardAttractor` or `SensorAttractor` later) but "closed for modification" (the particle update logic never has to change again).

### The "Installation" Mindset
* **Passive Interaction**: In a projection setting, the "user" is often a viewer. An autonomous system provides a continuous, evolving performance that doesn't "die" when no one is touching the computer.
* **WVGA Projection Aesthetics**: The mathematical curves of the `AutoAttractor` result in smooth, sweeping trails that emphasize the "Afterglow" effect from Step 5, turning the wall into a canvas of light.

## Learning Targets
* **C++ Inheritance**: Defining base and derived classes.
* **Virtual Functions**: Using the `virtual` keyword and the `override` specifier for runtime binding.
* **Abstract Classes**: Understanding pure virtual functions (`= 0`) and why they cannot be instantiated.
* **Dynamic Memory**: Using `new` and `delete` to manage object lifecycles on the heap.
* **Mathematical Animation**: Applying trigonometry to create complex, autonomous movement patterns.
* **Software Adaptability**: Writing code that behaves differently based on the deployment environment.

