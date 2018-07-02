![Imgur](https://i.imgur.com/tLicIC9.png)

# 3D CPU Engine
[![Build Status](https://travis-ci.org/GeekyMoose/3d-cpu-engine.svg?branch=master)](https://travis-ci.org/GeekyMoose/3d-cpu-engine)

| master | dev |
| :-----: | :-----: |
| [![Build Status](https://travis-ci.org/GeekyMoose/3d-cpu-engine.svg?branch=master)](https://travis-ci.org/GeekyMoose/3d-cpu-engine) | [![Build Status](https://travis-ci.org/GeekyMoose/3d-cpu-engine.svg?branch=dev)](https://travis-ci.org/GeekyMoose/3d-cpu-engine) |



## Description
This is a simple 3D Rendering Engine using CPU for learning purpose.
The main goal of this project is to understand low-level components of 3D engine.
For that reason, I use few libraries and try to re-implements everything such
as math library and drawing algorithms.


## Features
- Math library
    - Vectors 2
    - Vectors 3
    - Vectors 4
    - Matrix 3
    - Matrix 4
    - Matrix Transformations
        - Translation
        - Scaling
        - Rotations
        - LookAt
        - Perspective
        - Project 3D point into 2D screen
- Mesh
    - Loading from JSON (.babylon format)
- Rendering
    - Draw line
        - DDA algo
    - Draw filled triangle
        - Scanline Algorithm
        - Scanline Algorithm with z-buffering
        - Scanline Algorithm with z-buffering and Flat-Shading
        - Scanline Algorithm with z-buffering and Gouraud Shading
- Render Engine
    - Render loaded meshes (By default, render Suzanne monkey)
    - Zoom in / out
- SSE4.1 optimization (Used by math library)


## Requirements
- C++11
- `pragma once` support


## Dependencies
> Dependencies marked with *(CMake)* are automatically downloaded by CMake
> script and placed in *bin* folder.
> Others must be installed manually (Generally system-wide install).

- [SDL2](https://www.libsdl.org/) (**Must be installed system-wide**)
- [Boost property tree](http://www.boost.org/doc/libs/1_64_0/doc/html/property_tree.html) (**System-wide**)
- [GoogleTest](https://github.com/google/googletest) (CMake)


## Build instructions
### Build and run engine (CMake)
```bash
# Manual instructions
mkdir build
cd build
cmake ..
make -j2
make runEngine

# Automated script
./build.sh
```

### Build and run tests (CMake)
```bash
mkdir build
cd build
cmake ..
make -j2
make runAllTests

# Automated script
./build.sh
```


## Work in progress
As you may see, Gnu and Panda are working really hard on this project!
Sometime, they even forget to eat the bamboo.
(At least Panda, because Gnu probably prefers the emacs source code).

![Imgur](http://i.imgur.com/TYmfaEw.jpg)


## Screenshots
![Imgur](http://i.imgur.com/hMiDdnz.png)
![Imgur](http://i.imgur.com/OS8aK45.png)
![Imgur](http://i.imgur.com/794m2up.png)


## Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))
