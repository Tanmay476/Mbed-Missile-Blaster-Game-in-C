# Missile Blaster

An embedded arcade-style shooter game inspired by the classic *Missile Command*, built for the ARM Mbed microcontroller platform.

## Overview

Missile Blaster is a real-time action game where players defend a cluster of cities from incoming enemy missiles. Control a ground-based turret that moves horizontally and fires anti-missile projectiles to intercept enemy threats before they destroy your cities. The game ends when all cities are destroyed or the player's turret is hit.

## Gameplay

- **Objective**: Defend cities by shooting down incoming enemy missiles
- **Controls**:
  - Navigation switch (left/right) to move the turret horizontally
  - Fire button to launch defensive missiles
  - Pushbuttons for game control
- **Scoring**: Earn points for each enemy missile intercepted
- **Game Over**: Triggered when all cities are destroyed or the turret is hit

## Hardware Requirements

- **Microcontroller**: ARM Mbed LPC1768
- **Display**: 4D Systems uLCD-144-G2 (128x128 color LCD)
- **Input**:
  - Five-way navigation switch
  - Three pushbuttons
- **Audio**: Speaker for sound effects
- **Accelerometer**: MMA8452 (optional, for tilt controls)

## Dependencies

This project uses the following Mbed libraries:

- **4DGL-uLCD-SE** - LCD display driver
- **MMA8452** - Accelerometer library
- **Nav_Switch** - Navigation switch library
- **wave_player** - Audio playback library

Library references are managed through `.lib` files in the root directory.

## Project Structure

```
.
├── src/                        # Source files
│   ├── main.cpp                # Main game loop and initialization
│   ├── player.cpp              # Player turret logic and scoring
│   ├── missile.cpp             # Enemy missile behavior and collision
│   ├── city_landscape.cpp      # City rendering and status tracking
│   ├── hardware.cpp            # Hardware abstraction layer
│   └── doubly_linked_list.cpp  # Data structure implementation
│
├── include/                    # Header files
│   ├── globals.h               # Global constants and configurations
│   ├── hardware.h              # Hardware interface definitions
│   ├── player_public.h         # Player public interface
│   ├── player_private.h        # Player internal structures
│   ├── missile_public.h        # Missile public interface
│   ├── missile_private.h       # Missile internal structures
│   ├── city_landscape_public.h # City landscape public interface
│   ├── city_landscape_private.h# City landscape internal structures
│   └── doubly_linked_list.h    # Linked list data structure
│
├── lib/                        # External Mbed libraries
│   ├── 4DGL-uLCD-SE/           # LCD display driver
│   ├── MMA8452/                # Accelerometer library
│   ├── Nav_Switch/             # Navigation switch library
│   ├── wave_player/            # Audio playback library
│   └── *.lib                   # Mbed library reference files
│
├── docs/                       # Documentation
│   └── P2-checklist.pdf        # Project checklist and requirements
│
├── mbed.bld                    # Mbed build configuration
├── .gitignore                  # Git ignore rules
└── README.md                   # This file
```

### Key Components

**Source Files (src/):**
- **main.cpp** - Entry point and game loop orchestrating initialization, input handling, and overall game updates
- **player.cpp** - Manages the player's turret (position, movement, firing) and tracks score and remaining cities
- **missile.cpp** - Handles enemy missile behavior: spawning, updating positions, and detecting collisions
- **city_landscape.cpp** - Sets up the city landscape and updates city status when hit
- **hardware.cpp** - Hardware abstraction layer for the Mbed board (display, inputs, audio)
- **doubly_linked_list.cpp** - Custom linked list implementation for managing game entities

**Headers (include/):**
- Public headers define interfaces for each game component
- Private headers contain internal implementation details
- **globals.h** contains game-wide constants and configurations

## Building and Deployment

### Using Mbed Online Compiler

1. **Import Project**:
   - Go to [Mbed Online Compiler](https://ide.mbed.com/)
   - Import this repository
   - The compiler will automatically recognize the project structure

2. **Configure Build**:
   - Select target platform: **LPC1768**
   - Library dependencies will be resolved from the `lib/` directory

3. **Compile**:
   - Click "Compile" to generate a `.bin` file
   - The compiled binary will be downloaded to your computer

4. **Deploy to Hardware**:
   - Connect your Mbed LPC1768 via USB (it will appear as a removable drive)
   - Copy the compiled `.bin` file to the Mbed drive
   - Press the reset button on the board to run the game

### Using Mbed CLI

```bash
# Clone the repository
git clone <repository-url>
cd Mbed-Missile-Blaster-Game-in-C

# Deploy library dependencies
mbed deploy

# Compile for LPC1768
mbed compile -t GCC_ARM -m LPC1768

# Flash to board (if connected)
mbed compile -t GCC_ARM -m LPC1768 --flash
```

**Note**: Due to the restructured directory layout, you may need to update include paths in the Mbed build configuration if building locally. The Mbed Online Compiler should handle this automatically.

## Game Controls

- **Left/Right**: Move turret horizontally
- **Fire Button**: Launch defensive missile
- **Reset**: Restart game after Game Over

## Development

This project was developed as part of an embedded systems course, demonstrating:
- Real-time game loop implementation
- Hardware interfacing (display, inputs, audio)
- Memory-efficient data structures
- Collision detection algorithms
- State management in resource-constrained environments

## License

This project is provided as-is for educational purposes.