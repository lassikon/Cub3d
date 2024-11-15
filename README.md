# Our Cubed

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contact](#contact)

## Overview

**Our Cubed** is a raycasting game inspired by classic first-person shooters like *Wolfenstein 3D*. Built entirely in C, it uses **MLX42** as a graphics library dependency to render a  3D environment where players battle enemies. This project demonstrates fundamental game development techniques using raycasting and low-level C programming.

## Features

- **Raycasting Engine**: Creates a pseudo-3D view by simulating a 3D environment in 2D.
- **Demon Enemies**: Engage in combat with enemies in a classic FPS style.
- **Smooth Gameplay**: Efficient and optimized C code ensures fast and smooth performance.
- **Minimalist Graphics**: Uses MLX42 for rendering.
- **Minimap**: Helps player to orient themselves within the game world.
- **Sliding Doors**: Implements sliding doors.
- **Animated Sprites**: Implements animated sprites for enemies.


## Installation

1. **Clone the repository**:

   switch makefile MLX flags
   - Macos: `-Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/`
   - Linux: `-Iinclude -ldl -lglfw -pthread -lm`
   ```bash
   git clone git@github.com:lassikon/Cub3d.git
   cd Cub3d
   ```

2. **Compile the project**:

   ```bash
   make
   ```

## Usage

1. **Run the game**:

   ```bash
   ./Cub3d
   ```

2. **Gameplay**:
   - Move with **WASD**.
   - Jump with **Space**
   - Aim and shoot at the demons with mouse.
   - Try to survive as long as possible!

### Controls

- **Move**: W, A, S, D 
- **Shoot**: Left Mouse Button
- **Jump**: Space bar


## Contact

**Your Name**  
[Janrau's Email](janraup356@gmail.com)  
[Janrau's Linkedin](https://linkedin.com/in/janrau-beray)  
