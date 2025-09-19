cmake_minimum_required(VERSION 4.0)

project(SimplePiano)
set(EXECUTABLE_OUTPUT_PATH "bin")

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/PianoCore/external
    ${PROJECT_SOURCE_DIR}/lib/imgui
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/src
    )

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/assimp
    ${PROJECT_SOURCE_DIR}/glm
)
add_subdirectory(PianoCore)
add_subdirectory(PianoApp)

