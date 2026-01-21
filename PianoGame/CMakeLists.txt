cmake_minimum_required(VERSION 4.0)

project(PianoGame)
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
# find_package(glfw3 3.3 REQUIRED)
# find_package(OpenAL REQUIRED)
# find_package(OpenGL REQUIRED)
# find_package(ZLIB REQUIRED)
# add_definitions(-D GLM_ENABLE_EXPERIMENTAL)

file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/lib/imgui/**" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)


add_executable(PianoGame ${SRC_FILES})

target_include_directories(PianoGame PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/lib/imgui
    ${PROJECT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
message(OpenGlIncludeDir="${OPENGL_INCLUDE_DIRS}")

target_link_libraries(PianoGame
PianoCore
)


# # # Creating a library for integrating with Google Test, eventually this probably becomes a separate library that the main game imports...
# add_library(PianoGameLib
#     ${SRC_FILES}
# )
# target_link_libraries(PianoGameLib
# OpenGL::OpenGL
# glfw
# OpenAL::OpenAL
# assimp
# ZLIB::ZLIB
# fmt::fmt
# )


# Copying shaders and textures into the build directory for runtime compiling
add_custom_command(
         TARGET PianoGame POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/resources/shaders $<TARGET_FILE_DIR:PianoGame>/shaders
         COMMENT "Copying shaders" VERBATIM
         )

add_custom_command(
    TARGET PianoGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory              
        ${CMAKE_SOURCE_DIR}/resources/textures $<TARGET_FILE_DIR:PianoGame>/textures
    COMMENT "Copying textures" VERBATIM
    )

# # Unit testing
# enable_testing()
# add_subdirectory(tests)