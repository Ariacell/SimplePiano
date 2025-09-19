cmake_minimum_required(VERSION 4.0)

project(SimplePiano)
set(EXECUTABLE_OUTPUT_PATH "bin")

set(CMAKE_CXX_STANDARD 17)

#Enforce GLFW present for window management
find_package(glfw3 3.3 REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)
add_definitions(-D GLM_ENABLE_EXPERIMENTAL)


include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/lib/imgui
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/src
    )
message(OpenGlIncludeDir="${OPENGL_INCLUDE_DIRS}")

file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/lib/imgui/**" 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/lib/glad.c"
)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/assimp
    ${PROJECT_SOURCE_DIR}/glm
)

add_executable(SimplePiano ${SRC_FILES})

target_link_libraries(SimplePiano
OpenGL::OpenGL
glfw
OpenAL::OpenAL
assimp
ZLIB::ZLIB
)

# Copying shaders and textures into the build directory for runtime compiling
add_custom_command(
         TARGET SimplePiano POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/resources/shaders $<TARGET_FILE_DIR:SimplePiano>/shaders
         COMMENT "Copying shaders" VERBATIM
         )

add_custom_command(
    TARGET SimplePiano POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory              
        ${CMAKE_SOURCE_DIR}/resources/textures $<TARGET_FILE_DIR:SimplePiano>/textures
    COMMENT "Copying textures" VERBATIM
    )
