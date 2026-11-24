# Highway Rush

Highway Rush is a beginner-friendly 2D top-down highway game built for a
Computer Graphics course. It uses C++17, GLFW, and OpenGL compatibility-mode
drawing. The project now includes the **Week 10 driving loop**.

## Features

- A resizable 1280 x 720 GLFW window
- An OpenGL 2.1 compatibility context
- A fixed 1280 x 720 2D coordinate system with aspect-ratio preservation
- A three-lane highway, road edges, lane markings, and roadside scenery
- A top-down player car with smooth steering, acceleration, coasting, and braking
- Scrolling lane markings and road boundaries that keep the whole car on the asphalt
- Slower traffic that spawns in random lanes and moves relative to the player
- Axis-aligned bounding box (AABB) collisions that stop the run and allow a restart
- A double-buffered rendering loop and clean window shutdown

## Requirements

- A C++17 compiler
- CMake 3.16 or newer
- GLFW 3.3 or newer
- OpenGL development libraries
- Ninja (recommended, but another CMake generator also works)

## Build and run

From the project directory:

```bash
cmake -S . -B build -G Ninja
cmake --build build
./build/HighwayRush
```

| Controls | Action |
|---|---|
| **Left / Right** or **A / D** | Steer across the road. |
| **Up** or **W** | Accelerate from a standstill. Release to coast. |
| **Down** or **S** | Brake to a stop. |
| **R** | Restart after a crash. |
| **Escape** | Exit the game. |

## Project files

| File | Purpose |
|---|---|
| `CMakeLists.txt` | Defines the C++ program and links GLFW and OpenGL. |
| `src/main.cpp` | Starts GLFW, creates the window, runs the loop, and shuts down. |
| `include/Game.h`, `src/Game.cpp` | Own the scene, update traffic, and handle collisions and restarts. |
| `include/Renderer.h`, `src/Renderer.cpp` | Set the 2D projection, clear the frame, and provide basic shape functions. |
| `include/Road.h`, `src/Road.cpp` | Draw the road, three lanes, shoulders, and scenery. |
| `include/Player.h`, `src/Player.cpp` | Update speed and steering, check overlaps, and draw the player car. |
| `include/TrafficCar.h`, `src/TrafficCar.cpp` | Store positions and draw the traffic cars. |
| `AGENTS.md` | Records scope and simplicity rules for future development. |
| `.gitignore` | Keeps generated build and editor files out of Git. |

## How the program works

### Window and OpenGL context

`glfwInit` starts GLFW. Window hints request OpenGL 2.1, whose standard context
supports the compatibility functions taught in the course. `glfwCreateWindow`
creates the operating-system window and its OpenGL context, and
`glfwMakeContextCurrent` selects that context for drawing.

### Coordinate system

`glOrtho(0, 1280, 0, 720, -1, 1)` creates a simple 2D world. The origin `(0,
0)` is at the bottom-left, x increases to the right, and y increases upward.
The resize callback uses letterboxing so the world keeps its 16:9 shape.

### Drawing

Every visible object is built with `GL_QUADS`, `GL_POLYGON`, or
`GL_TRIANGLE_FAN`. Vertices describe corners in 2D. Colors are selected with
`glColor3f`. The player uses `glTranslatef` inside `glPushMatrix` and
`glPopMatrix`, which moves the whole car while protecting the rest of the
scene from that transformation.

### Rendering loop

The main loop collects GLFW events, reads the controls, updates the game using
elapsed time in seconds, redraws the scene, and swaps the hidden back buffer
onto the screen.
Double buffering prevents the user from seeing a partly drawn frame. The loop
ends when the user closes the window or presses Escape.

### Week 10 gameplay

The player holds a fixed vertical position. Forward speed moves the lane
markings downward, and the dash pattern repeats after each dash and gap.
Steering gradually changes the car's sideways velocity and clamps its position
so the wheels stay on the asphalt.

Traffic enters beyond the top of the screen after the player gains enough
distance on it. Cars move down the screen while the player is faster, move
upward when the player slows below traffic speed, and are removed once they
leave the view.

Each frame checks whether the player and a traffic car overlap on both the
x and y axes. A collision freezes the scene and shows the restart prompt in
the window title.

## Computer Graphics concepts demonstrated

- 2D primitives: rectangles, a polygon, and triangle-fan circles
- Translation: the car is drawn around a local origin and translated into place
- Coordinate systems: local car coordinates and the 1280 x 720 world
- Colors: RGB values distinguish road, scenery, body, windows, and lights
- Clipping: OpenGL clips drawing outside the orthographic view and viewport
- Double buffering: GLFW swaps completed frames for smooth display
