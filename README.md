# 3D Software Engine
> A simple 3D Rendering Engine using CPU for learning purpose.

[![Build Status](https://travis-ci.org/GeekyMoose/3d-soft-engine.svg?branch=master)](https://travis-ci.org/GeekyMoose/3d-soft-engine)

![Imgur](http://i.imgur.com/hMiDdnz.png)
![Imgur](http://i.imgur.com/794m2up.png)


# Description
This project is a simple 3D Software Engine.
Soft means that only CPU is used.
The main goal of this project is to understand low-level components of 3D game engine.
For that reason, I use few libraries and try to re-implements everything.
(For instance, the math library, drawing algorithm etc).
This is for the learning purpose. (Otherwise, SDL already implements these algorithms).


# Work in progress.
> As you see, Gnu and Panda are working really hard on this project!
> Sometime, they even forget to eat the bamboo.
(At least Panda, because Gnu probably prefers eating the emacs source code).

![Imgur](http://i.imgur.com/TYmfaEw.jpg)


# Dependencies
- [CMake](https://cmake.org/) (Build system)
- [Boost property tree](http://www.boost.org/doc/libs/1_64_0/doc/html/property_tree.html) (For JSON parsing)
- [GoogleTest](https://github.com/google/googletest) (For Unit Tests)
- [SDL2](https://www.libsdl.org/)

> SDL2 and Boost must be installed on your computer.
> SDL2 is automatically find by CMake.
> GoogleTest is automatically downloaded and build by CMake.


# Build and run the project on Linux
> Require C++11. Compiled and tested with gcc 6.3.0
> (Require pragma once support)

```
mkdir build
cd build
cmake ..
make
make runengine
```

You can run manually with `./src/3d-soft-engine` or run on gdb with
```
cd src
gdb ./3d-soft-engine
```

# Build and run the project on Windows
Not supported

# Build and run the project on Mac
Not supported

# Start Unit Tests
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
- SSE optimizations
	- ON to use SSE (Force to use even if you don't support. But it will fail then)
	- OFF to disable SSE (Default option)
- Unit test
	- ON to also build tests (Default option)
	- OFF to disable tests


# Features
- Math library (Header only)
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
		- Project 3D point into 2D screen `new`
- Mesh
	- Loading from JSON (.babylon format)
- Rendering
	- Draw line
		- DDA algo
	- Draw filled triangle
		- Scanline Algorithm
		- Scanline Algorithm with z-buffering
		- Scanline Algorithm with z-buffering and flat-shading `new`
- SSE4.1 optimization (Used by math library)
- Engine
	- Render loaded meshes (By default, render Suzanne monkey)
	- Zoom in / out


# Screenshots
![Imgur](http://i.imgur.com/hMiDdnz.png)
![Imgur](http://i.imgur.com/whVWbI2.png)
![Imgur](http://i.imgur.com/794m2up.png)
![Imgur](http://i.imgur.com/92bPmsc.png)


# Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))
