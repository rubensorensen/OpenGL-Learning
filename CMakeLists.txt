cmake_minimum_required(VERSION 3.20)
project(OpenGL_Learning)

set(CMAKE_CXX_STANDARD 20)

add_executable(OpenGL_Learning "")

target_sources(OpenGL_Learning
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/Application.cpp
        PUBLIC
)

target_include_directories(OpenGL_Learning
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src
        )