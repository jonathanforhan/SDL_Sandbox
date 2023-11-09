cmake_minimum_required(VERSION 3.20)
project(SDL_Sandbox)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options("/EHsc")
endif ()

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(sandbox)