cmake_minimum_required(VERSION 3.20)
project(OpenGL_Learning)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenGL_Learning "")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/extern/glfw)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/extern/glew)

target_sources(OpenGL_Learning
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/pch.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Application.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Renderer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/VertexBuffer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/IndexBuffer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/VertexArray.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/Renderer.h
        ${CMAKE_CURRENT_LIST_DIR}/src/IndexBuffer.h
        ${CMAKE_CURRENT_LIST_DIR}/src/VertexArray.h
        ${CMAKE_CURRENT_LIST_DIR}/src/VertexBufferLayout.h
    )

target_include_directories(OpenGL_Learning
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/extern/glfw/include
        ${CMAKE_CURRENT_LIST_DIR}/extern/glew/include
    )

target_precompile_headers(OpenGL_Learning
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/pch.h
    )


target_link_libraries(OpenGL_Learning
    PUBLIC
        glfw
        libglew_static
    )