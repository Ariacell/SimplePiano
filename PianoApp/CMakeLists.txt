add_executable(PianoApp main.cpp)

target_link_libraries(PianoApp PRIVATE PianoCore)

target_include_directories(PianoApp
    PRIVATE
        ${PROJECT_SOURCE_DIR}/PianoCore/src
)

# Copying shaders and textures into the build directory for runtime compiling
add_custom_command(
         TARGET PianoApp POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_SOURCE_DIR}/resources/shaders $<TARGET_FILE_DIR:PianoApp>/shaders
         COMMENT "Copying shaders" VERBATIM
         )

add_custom_command(
    TARGET PianoApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory              
        ${CMAKE_SOURCE_DIR}/resources/textures $<TARGET_FILE_DIR:PianoApp>/textures
    COMMENT "Copying textures" VERBATIM
    )