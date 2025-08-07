# Missile Blaster (Mbed Game in C)

## Gameplay

Missile Blaster is an embedded arcade-style shooter inspired by the classic *Missile Command* game. The player controls a turret that can move horizontally and shoot anti-missile projectiles to defend a cluster of cities at the bottom of the screen. Enemy missiles randomly descend from the top; if they reach the ground or hit a city, that city is demolished. The goal is to shoot down these incoming missiles before they destroy all the cities. You gain points for each enemy missile intercepted, and the game ends when the player's turret is destroyed or all cities are gone (triggering a Game Over).

## Hardware and Platform

This project is built on the ARM Mbed microcontroller platform. It uses a small color LCD screen for the game display, along with on-board input controls (three pushbuttons and a five-way navigation switch) for player movement and firing. A small speaker provides basic sound effects. The code is written in C/C++ using Mbed libraries to interface with these hardware components.

## Main Source Files

* **main.cpp** – Entry point and game loop orchestrating initialization, input handling, and overall game updates.
* **player.cpp / player.h** – Manages the player’s turret (position, movement, firing) and tracks the score and remaining cities.
* **missile.cpp / missile.h** – Handles enemy missile behavior: spawning missiles over time, updating their positions, and detecting collisions.
* **city\_landscape.cpp / city\_landscape.h** – Sets up the city landscape at the bottom of the screen and updates city status when hit (drawing cities intact or demolished).
* **hardware.cpp / hardware.h** – Hardware abstraction layer for the Mbed board (initializes the display, inputs, etc., and reads user input into a GameInputs structure).
