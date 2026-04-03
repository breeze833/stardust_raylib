# Project: Digital Stardust

An iterative exploration of generative art using C++ and raylib. This project evolves from a simple bouncing particle into a complex autonomous installation.

## Prerequisites
- C++ Compiler (e.g., `g++`)
- [raylib](https://www.raylib.com/) installed on your system.
- X11 development libraries (required on Linux for raylib, e.g., `-lX11`).

## How to Build
Run `make` in the root directory. The binary will be generated as `./stardust`.

## Evolutions of the Program
This project will evolve for several versions. Here we will list the versions:

- **Initial version**: Ensure the build tools and libraries are ready.
- **Step 1 (v1)**: Make a single bouncing ball on the screen with frame-rate independent movement. See [doc/step1.md](doc/step1.md) for details.
- **Step 2 (v2)**: Introduce a multi-particle system with randomized properties and modular code structure. See [doc/step2.md](doc/step2.md) for details.
- **Step 3 (v3)**: Implement dynamic inter-particle connections based on proximity to create a web-like visual effect. See [doc/step3.md](doc/step3.md) for details.
- **Step 4 (v4)**: Introduce user interaction with a mouse-triggered gravity impulse and implement acceleration-based physics with damping. See [doc/step4.md](doc/step4.md) for details.
