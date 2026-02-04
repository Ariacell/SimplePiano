
# The piano Project

This project is intended as a c++ learning experience, a game engine API design exercise, and potentially a small game PoC if I decide it's worthwhile/feel inspired.

The components consist of the PianoCore library - the core engine, and PianoGame - a simple smoke testing environment validate the behaviour of the engine.

CURRENT UP NEXT: Ideally PianoCore includes unit tests now that I've split it from the smoke testing game project

[Roadmap](./docs/)

# References for working on this project

See the [building locally section](#building-locally) for some intructions on building and running the project

## GLFW
The main input and window management library for the project.
https://www.glfw.org/GLFWReference276.pdf

## OpenGL Rendering
The first rendering pipeline implemented - the plan is to use this project to also experiment with hotswappable Vulkan/DX12

https://learnopengl.com

## DX11/12 Rendering

To come once I decide how I want to do hotswapping of the renderer

## Vulkan

To come once I decide how I want to do hotswapping of the renderer

# Building locally

## First time setup

```
sudo apt install clang-format clang-tidy
```

## Requirements
This project is built via CMake, and requires the following libraries/packages installed to build from source:

- [OpenGL (Rendering)](#opengl)
- OpenAL (Audio) 
- GLFW (Window Management) 
- [Assimp](#assimp)


All other dependencies such as Imgui and GLAD loaders are included, and assuming the prerequisites are satisfied, you should be able to build from source via

```sh
cmake --preset <name-of-preset>
cmake --build --preset <name-of-preset>
```

If using VSCode as I do at the moment, F5 should automatically build and run the process via gdb for debugging.
Release task configuration to be done later once it's worthwhile building a release binary.

### OpenGL

On linux distros, something like the following may help for debian:
```
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

### Assimp
Assimp is too large to bundle with the project on public github.
In order to build this project from source, you will need to build it locally/already the library file built, and drop it into the lib/assimp directory.

TODO: Improve build instructions for this step
For now, follow this instructions on the [Assimp project wiki](https://github.com/assimp/assimp/blob/master/Build.md), building the file with
```sh
cmake CMakeLists.txt -dBUILD_SHARED_LIBS=OFF
```


### Debugging dependencies

This is a really cool command for visualising CMake project dependencies
```sh
cmake --graphviz=dependencies.dot .
dot -Tpng dependencies.dot -o dependencies.png
```


## Learning record

Since the goal of this project is also a lot about (re)learning c++ and systems level concepts I haven't had the chance to use much in my day-to-day, I'll record some of the tricky things I encounter along the way to help lock in learning as I go :D

Some stuff that ate up debugging time:

VSCode not working super great ootb the C++ includes paths, still refining this but seems much better with CMake extensions so far, was able to successfully split the repo into the core library and the PoC game layer I'm using on top

learn opengl tutorial apparently uses an older API based on my research after going through the first sections of the tutorial, could probably simplify my life by updating the pattern used for binding VAO/VBOs to use index buffers

General basic c++ concepts such as object lifetimes and ownership. I've worked for so long in more functional paradigms (e.g. Typescript, Kotlin, F#) that worrying about stateful systems is something I've had to get used to again, but I think I'm back at a reasonable level of comfort now (outside of fancier move/implicit cast shenanigans)

Argument forwarding and default constructors 

smart pointers -> I think I'm forming the opinion that I agree with the position that std::shared_ptr is *usually* a smell, in the sense that I don't see many cases where an object has a legitimate reason for shared ownership outside of very special cases, but perhaps again that's just more bias against mutable state. Blurring the boundaries of ownership of an object seems to be just asking for trouble unless that object is sufficiently large or cumbersome to pass around as to warrant this loss of determinism on the ownership side.