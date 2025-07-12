
# References for working on this project

## GLFW
https://www.glfw.org/GLFWReference276.pdf

# Building locally

## Requirements
This tool requires the following libraries to build:

OpenGL (Rendering)
OpenAL (Audio)
GLFW (Window Management)

sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

All other dependencies such as Imgui and GLAD loaders are included, and you should be able to build from source via
```
cmake --build --preset default
```
or if using VSCode as I do at the moment, F5 should automatically build and run the process via gdb for debugging.
Release task configuration to be done later once it's worthwhile building a release binary.