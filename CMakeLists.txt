cmake_minimum_required(VERSION 3.10)

project(SimplePiano)
set(EXECUTABLE_OUTPUT_PATH "bin")

set(CMAKE_CXX_STANDARD 17)

#Enforce GLFW present for window management
find_package(glfw3 3.3 REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/imgui 
    ${PROJECT_SOURCE_DIR}/lib 
    ${PROJECT_SOURCE_DIR}/src
    ${GLUT_INCLUDE_DIRS}
    )
    
file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/imgui/*.cpp" 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/lib/**/*.c"
    "${PROJECT_SOURCE_DIR}/lib/**/*.cpp"
)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/imgui 
)

add_executable(SimplePiano ${SRC_FILES})
target_link_libraries(SimplePiano
OpenGL::OpenGL
${GLUT_LIBRARY}
glfw
OpenAL::OpenAL
)

