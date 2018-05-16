![Imgur](http://i.imgur.com/OS8aK45.png)


# 3D CPU Engine
[![Build Status](https://travis-ci.org/GeekyMoose/3d-soft-engine.svg?branch=master)](https://travis-ci.org/GeekyMoose/3d-soft-engine)

> A simple 3D Rendering Engine using CPU for learning purpose.


# Description
This is a simple 3D CPU Engine.
The main goal of this project is to understand low-level components of 3D game engine.
For that reason, I use few libraries and try to re-implements everything.
As an example, math and drawing libraries are re-implemented from scratch.
This is for the learning purpose.


# Features
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
- SSE4.1 optimization (Used by math library)
- Engine
    - Render loaded meshes (By default, render Suzanne monkey)
    - Zoom in / out


# Dependencies
- [Boost property tree](http://www.boost.org/doc/libs/1_64_0/doc/html/property_tree.html) (For JSON parsing)
- [GoogleTest](https://github.com/google/googletest) (For Unit Tests)
- [SDL2](https://www.libsdl.org/) (Window)

> SDL2 and Boost must be installed on your computer.

> SDL2 is automatically find by CMake. (If installed)

> GoogleTest is automatically downloaded and build by CMake.


# Build and run the project (CMake)
- Only Linux is supported. (Compiled and tested with gcc 6.3.0)
- [CMake](https://cmake.org/) (Build system)

> Requires C++11.

> Requires pragma once support

```
mkdir build
cd build
cmake ..
make
make run
```

You can run manually with `./src/3d-soft-engine` or run on gdb with
```
cd src
gdb ./3d-soft-engine
```


# Build and run Unit Tests (CMake)
```
mkdir build
cd build
cmake ..
make
make test
```

You can start a test manually with `./test/testToStart`


# Set CMake variables
CMake variables may be used to set several options.
- `ENGINE_ENABLE_TESTS`
    - ON to build tests.
    - OFF to disable tests.
- `ENGINE_ENABLE_SSE`
    - ON to automatically detect and use SSE. If no SSE support found, skip it.
    - OFF to disable SSE.
- `-DCMAKE_BUILD_TYPE`
    - Default CMake build type. See https://cmake.org/cmake/help/v3.0/variable/CMAKE_BUILD_TYPE.html


# Work in progress.
> As you may see, Gnu and Panda are working really hard on this project!
> Sometime, they even forget to eat the bamboo.
> (At least Panda, because Gnu probably prefers the emacs source code).

![Imgur](http://i.imgur.com/TYmfaEw.jpg)


# Screenshots
![Imgur](http://i.imgur.com/hMiDdnz.png)
![Imgur](http://i.imgur.com/OS8aK45.png)
![Imgur](http://i.imgur.com/794m2up.png)


# Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))
