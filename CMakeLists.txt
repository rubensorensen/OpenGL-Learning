cmake_minimum_required(VERSION 3.20)
project(OpenGL_Learning)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenGL_Learning "")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/extern/glfw)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/extern/glew)

target_sources(OpenGL_Learning
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/Application.cpp
    PUBLIC
    )

target_include_directories(OpenGL_Learning
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/extern/glfw/include
        ${CMAKE_CURRENT_LIST_DIR}/extern/glew/include
    )


target_link_libraries(OpenGL_Learning
    PUBLIC
        glfw
        libglew_static
    )