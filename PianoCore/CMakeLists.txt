cmake_minimum_required(VERSION 4.0)

project(PianoCore)

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


include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    )
message(OpenGlIncludeDir="${OPENGL_INCLUDE_DIRS}")

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/**" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/glm
)


# # Creating a library for integrating with Google Test, eventually this probably becomes a separate library that the main game imports...
add_library(PianoCore STATIC
    ${SRC_FILES}
)

## Add assimp
add_library(assimp STATIC IMPORTED)

set_target_properties(assimp PROPERTIES
    IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/assimp/libassimp.a
    INTERFACE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)
target_link_libraries(PianoCore
    PRIVATE
        assimp
)


## Link glad so that I avoid whatever mess I'm doing in PianoGame
add_library(glad STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glad.c"
)

target_include_directories(glad
    PUBLIC vendor
)

target_link_libraries(PianoCore
    PUBLIC glad
)


target_include_directories(PianoCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${OPENGL_INCLUDE_DIRS}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(PianoCore
PUBLIC
OpenGL::OpenGL
glfw
OpenAL::OpenAL
ZLIB::ZLIB
fmt::fmt

)
