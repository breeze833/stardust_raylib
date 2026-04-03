# Step 4: The Force (Interactivity and Acceleration)

## Goal
The goal of this version is to introduce user interactivity and transition from constant velocity to acceleration-based physics. By using the mouse as a "Gravity Source," the program allows users to influence the trajectory of all particles in real-time. This version also introduces basic fluid-like damping to the system.

## Design
This stage shifts the simulation from a "passive observer" experience to an "active participant" experience:
1.  **Gravity Parameters**: A `gravityStrength` (10000.0f) is added to the `config` struct to control the intensity of the attraction impulse.
2.  **Input Detection**: The program checks for a mouse click using `IsMouseButtonPressed(MOUSE_BUTTON_LEFT)`. If triggered, it retrieves the current coordinates (`GetMousePosition`).
3.  **The Attractor**: When clicked, the mouse position acts as a temporary point of infinite mass, applying a gravity force to all particles for that frame.
4.  **Optional Values**: The use of `std::optional<Vector2>` ensures that the gravity force is only applied when the mouse event is detected.
5.  **Damping and Minimum Velocity**: To maintain simulation stability and prevent infinite acceleration, a `damping` factor (0.998f) and a `minVelocity` threshold (50.0f) are introduced.

## Algorithms
### Newton’s Second Law (Impulse Acceleration)
To simulate the pull toward the mouse click, the `update_particle` function calculates a force vector for every particle:
1.  **Direction Vector**: Calculate the displacement between the mouse ($M$) and the particle ($P$):
    $$\vec{v}_{dir} = \vec{M} - \vec{P}$$
2.  **Normalization**: Convert the direction into a **unit vector** (length of 1) so that acceleration magnitude is independent of the distance:
    $$\hat{u} = \frac{\vec{v}_{dir}}{|\vec{v}_{dir}|}$$
3.  **Acceleration**: Multiply the unit vector by the `gravityStrength`:
    $$\vec{a} = \hat{u} \times \text{strength}$$
4.  **Euler Integration**: Update the velocity by adding acceleration scaled by $\Delta t$, and then update the position based on the new velocity:
    $$\vec{v}_{new} = (\vec{v}_{old} + \vec{a} \times \Delta t) \times \text{damping}$$
    $$\vec{pos}_{new} = \vec{pos}_{old} + \vec{v}_{new} \times \Delta t$$

## Theories
### Vector Fields and Damping
* **Normalization and Constant Force**: By normalizing the direction vector, the program applies a uniform force regardless of how far the mouse is from the particle, simplifying the simulation and ensuring consistent results.
* **Friction and Damping**: Without damping, energy would never leave the system. The `damping` factor simulates a resistant medium (like air or water), causing particles to eventually slow down toward the `minVelocity` threshold.
* **Euler Integration**: This version moves to a more sophisticated "Update-after-Update" model where position depends on velocity, and velocity depends on acceleration.

## Learning Targets
* **Raylib Interactivity**: Using `IsMouseButtonPressed` and `GetMousePosition` for event-driven simulation.
* **Modern C++ Features**: Utilizing `<optional>` and `std::optional` for handling conditional state.
* **Physics Modeling**: Implementing acceleration-based motion and velocity damping.
* **Raymath Library**: Mastering `Vector2Subtract`, `Vector2Normalize`, `Vector2Scale`, `Vector2Add`, and `Vector2Length`.
* **Stability in Simulations**: Understanding the roles of thresholding (`minVelocity`) and scaling (`damping`) in preventing chaotic numerical instability.
