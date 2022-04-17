cmake_minimum_required(VERSION 3.5)

project(debugger)

add_library(linenoise STATIC 
    src/linenoise.c
)

target_include_directories(linenoise
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

add_executable (debugger_ 
    src/debugger.cpp
)

target_link_libraries (debugger_
     PRIVATE 
        linenoise
)