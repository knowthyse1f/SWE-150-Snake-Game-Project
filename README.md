# Snake Game using SDL2 and C++

This is a classic Snake game implemented using the SDL2 graphics library in C++. The game features a single class called `Snake` with 15 functions to ensure efficient and understandable code.

## Features

1. **Snake Body**: The snake is represented by a series of connected segments.
2. **Snake Movement**: The snake moves in response to player input.
3. **Generate Food**: Food is generated randomly on the screen for the snake to eat.
4. **Bonus Generation**: After eating a certain amount of food, a bonus item is generated.
5. **Self-Collision Detection**: The game checks if the snake collides with itself.
6. **Boundary Collision Detection**: The game checks if the snake collides with the boundaries of the screen.
7. **Fixed Obstacles**: Obstacles are generated in fixed positions on the screen.
8. **Obstacle Collision Detection**: The game checks if the snake collides with the obstacles.
9. **Score Display**: The current score is displayed on the screen.
10. **High Score Saving**: The highest score is saved and displayed.

## Requirements

- C++ Compiler
- SDL2 Library

## Setup

1. **Install SDL2**:
   - On Ubuntu: `sudo apt-get install libsdl2-dev`
   - On macOS: `brew install sdl2`
   - On Windows: Download and install from the [SDL2 website](https://www.libsdl.org/download-2.0.php).

2. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd snake-game
