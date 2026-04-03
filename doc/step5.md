# Step 5: The Afterglow (Motion Blur and Alpha Trails)

## Goal
The goal of this version is to transition from a "clean" frame-by-frame rendering to a "persistent" one. By modifying how the screen is cleared each frame, the program creates a motion blur effect where particles and connections leave luminous trails (afterglow). This transforms the simulation from a set of moving dots into a fluid, organic piece of generative art.

## Design
This stage introduces the concept of temporal blending—using the state of previous frames to influence the current one:
1.  **Trail Parameters**: A `trailAlpha` value (20) is added to the `config` struct to control the length and persistence of the trails.
2.  **The Partial Clear**: The standard `ClearBackground(BLACK)` command is removed. It is replaced by `DrawRectangle` covering the full screen with a semi-transparent black color (`clearColor = { 0, 0, 0, config.trailAlpha }`).
3.  **Temporal Persistence**: Because the background is only "partially" blacked out each frame, previous positions of particles and connection lines remain visible, gradually fading into the background.
4.  **Radius Tuning**: The particle `radius` is reduced to 3.0f to accommodate the increased visual density created by the trails.

## Algorithms
### The Persistence Algorithm (Accumulation via Overdraw)
The "Motion Blur" effect is achieved by accumulating color in the frame buffer over multiple frames:
1.  **Frame Start**: Instead of wiping the entire frame buffer, draw a full-screen rectangle:
    * `Color clearColor = { 0, 0, 0, config.trailAlpha };`
    * `DrawRectangle(0, 0, config.screenWidth, config.screenHeight, clearColor);`
2.  **Fading Logic**: 
    * Each frame, existing pixel colors are blended with a layer of ~7.8% (20/255) black.
    * This exponential decay means older frames become increasingly dim but never immediately disappear.
    * Fast-moving particles (accelerated by the gravity impulse from Step 4) leave long, sweeping trails, while slow particles appear to have a soft "aura."

## Theories
### Persistence of Vision and Temporal Blending
* **Simulated Motion Blur**: In computer graphics, we simulate the "shutter speed" of a camera by not fully erasing the "memory" of the screen. This creates a sense of continuity in motion.
* **Alpha Blending as a Temporal Tool**: This technique demonstrates that the Alpha channel can be used to control "history" or "decay" in a visual system.
* **Aesthetic Smoothing**: Motion blur hides the discrete nature of digital frames, making the movement appear more fluid and high-fidelity, which is especially effective for large-scale projections.

## Learning Targets
* **Custom Clearing Methods**: Understanding why and how to replace `ClearBackground` with manual screen-space fills for visual effects.
* **Alpha Channel Mastery**: Learning how low alpha values behave when stacked and blended over time.
* **Visual Density Balance**: Adjusting parameters like `radius` and `trailAlpha` to maintain clarity while adding complex visual effects.
* **Generative Art Techniques**: Recognizing how simple changes in the rendering pipeline (like persistence) can dramatically change the artistic quality of a simulation.
* **Performance Considerations**: Observing that this technique is computationally inexpensive (a single full-screen rectangle) compared to sophisticated post-processing shaders, making it ideal for low-power hardware.
