
# Requirements
This tool requires the following libraries to build:

OpenGL (Rendering)
OpenAL (Audio)
GLFW (Window Management)

sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

All other dependencies such as Imgui and GLAD loaders are included, and you should be able to build from source via
```
cmake .
make
```