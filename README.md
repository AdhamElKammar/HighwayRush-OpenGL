# Highway Rush

Highway Rush is a 2D top-down driving game where you dodge traffic on a three-lane highway.
It is built with C++17, GLFW, and OpenGL.

## Features

- Smooth steering, acceleration, coasting, and braking with WASD or the arrow keys.
- Scrolling lane markings that match your speed.
- Road boundaries that keep your car on the asphalt.
- Slower traffic that appears in random lanes.
- Collisions that end the run. Press **R** to restart.
- A resizable window that preserves the game's 16:9 aspect ratio.

## Build and run

Install a C++17 compiler, CMake 3.16 or newer, Ninja, GLFW 3.3 or newer, and
the OpenGL development libraries for your system.

Open a terminal in the project directory. Configure the build, compile the
game, and launch it with these commands:

```bash
cmake -S . -B build -G Ninja
cmake --build build
./build/HighwayRush
```

## How to play

You start at a standstill in the middle lane. Accelerate to catch up to
traffic, then steer around slower cars or brake to let them pull ahead.
If you hit another car, the game freezes and the window title shows the
restart prompt.

| Keys | Action |
| --- | --- |
| **A / D** or **Left / Right** | Steer left or right. |
| **W** or **Up** | Accelerate. Release the key to coast. |
| **S** or **Down** | Brake to a stop. |
| **R** | Start a new run after a collision. |
| **Esc** | Quit the game. |

## Upcoming features

- A score based on distance driven.
- An on-screen speed and score display.
- A main menu with options to start and quit the game.
