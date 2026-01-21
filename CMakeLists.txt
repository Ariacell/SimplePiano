cmake_minimum_required(VERSION 4.0)

project(SimplePiano)
set(EXECUTABLE_OUTPUT_PATH "bin")

set(CMAKE_CXX_STANDARD 20)
option(CMAKE_COMPILE_WARNING_AS_ERROR "Compile warnings as errors" ON)
# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=blah-*)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

#Enforce GLFW present for window management
find_package(glfw3 3.3 REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)
add_definitions(-D GLM_ENABLE_EXPERIMENTAL)

# Add the pianocore library and the sample game environment
add_subdirectory(PianoCore)
add_subdirectory(PianoGame)
