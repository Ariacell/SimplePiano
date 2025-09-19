add_library(PianoCore STATIC)

file(GLOB_RECURSE PIANOCORE_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

#Enforce GLFW present for window management
find_package(glfw3 3.3 REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)
add_definitions(-D GLM_ENABLE_EXPERIMENTAL)

target_sources(PianoCore PRIVATE ${PIANOCORE_SOURCES})

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/external
    ${PROJECT_SOURCE_DIR}/lib/imgui
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/src
    )

target_include_directories(PianoCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${OPENGL_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/external
        ${PROJECT_SOURCE_DIR}/lib/imgui
        ${PROJECT_SOURCE_DIR}/lib/assimp
)

target_link_libraries(PianoCore
PRIVATE
    OpenGL::OpenGL
    glfw
    OpenAL::OpenAL
    ZLIB::ZLIB
)
