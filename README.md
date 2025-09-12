
# References for working on this project

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