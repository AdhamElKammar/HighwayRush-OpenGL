# Highway Rush

Highway Rush is a beginner-friendly 2D top-down highway game built for a
Computer Graphics course. It uses C++17, GLFW, and OpenGL compatibility-mode
drawing. This repository currently contains **Week 9 only**: the visual and
project foundation on which gameplay will be added later.

## Current Week 9 features

- A resizable 1280 x 720 GLFW window
- An OpenGL 2.1 compatibility context
- A fixed 1280 x 720 2D coordinate system with aspect-ratio preservation
- A three-lane highway, road edges, lane markings, and roadside scenery
- A stationary top-down player car made entirely from simple primitives
- A double-buffered rendering loop and clean window shutdown
- Escape key support for closing the application

Traffic, movement, scoring, collision detection, and menus are intentionally
not part of Week 9.

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

Press **Escape** or close the window to exit.

## Project files

| File | Purpose |
|---|---|
| `CMakeLists.txt` | Defines the C++ program and links GLFW and OpenGL. |
| `src/main.cpp` | Starts GLFW, creates the window, runs the loop, and shuts down. |
| `include/Game.h`, `src/Game.cpp` | Own the Week 9 scene and connect resizing to rendering. |
| `include/Renderer.h`, `src/Renderer.cpp` | Set the 2D projection, clear the frame, and provide basic shape functions. |
| `include/Road.h`, `src/Road.cpp` | Draw the road, three lanes, shoulders, and scenery. |
| `include/Player.h`, `src/Player.cpp` | Store and draw the stationary player car. |
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

The main loop reads the Escape key, clears and redraws the complete scene,
swaps the hidden back buffer onto the screen, and asks GLFW for new events.
Double buffering prevents the user from seeing a partly drawn frame. The loop
ends when the user closes the window or presses Escape.

## Computer Graphics concepts demonstrated

- 2D primitives: rectangles, a polygon, and triangle-fan circles
- Translation: the car is drawn around a local origin and translated into place
- Coordinate systems: local car coordinates and the 1280 x 720 world
- Colors: RGB values distinguish road, scenery, body, windows, and lights
- Clipping: OpenGL clips drawing outside the orthographic view and viewport
- Double buffering: GLFW swaps completed frames for smooth display

Rotation, scaling, and animation will be more meaningful once movement begins,
so they are reserved for later weeks.

## Week 10 plan

Week 10 will add smooth player steering, acceleration and braking, scrolling
lane markings, road-boundary constraints, traffic spawning and movement, and
simple AABB collision detection. Those systems are not implemented yet.
