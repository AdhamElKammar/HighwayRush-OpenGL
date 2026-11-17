# Highway Rush Development Guide

## Project scope

Highway Rush is a beginner-friendly C++17 and OpenGL university project. Follow
the weekly plan in `README.md`. Do not add features from a later week unless the
student explicitly requests them.

## Code style

- Prefer small classes, short functions, and descriptive names.
- Use basic C++ constructs; avoid templates, inheritance, and design patterns
  unless they solve a real requirement.
- Use OpenGL compatibility-profile immediate-mode drawing (`glBegin`,
  `glEnd`, and matrix transformations).
- Keep gameplay state separate from drawing where practical.
- Explain non-obvious formulas and OpenGL state changes with concise comments.
- Do not add third-party dependencies without permission.

## Building and testing

Configure with `cmake -S . -B build -G Ninja`, build with
`cmake --build build`, and run `./build/HighwayRush`. Preserve warning flags and
fix new warnings. Report honestly when a graphical test cannot be performed.

