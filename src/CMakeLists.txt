file(GLOB_RECURSE C_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB_RECURSE CXX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(SDL_ENGINE STATIC)

if (MSVC)
    set_target_properties(SDL_ENGINE PROPERTIES COMPILE_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
else ()
    set_target_properties(SDL_ENGINE PROPERTIES COMPILE_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif ()

target_sources(SDL_ENGINE PUBLIC ${C_SOURCES} ${CXX_SOURCES})
target_include_directories(SDL_ENGINE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SDL_ENGINE PUBLIC SDL3::SDL3 SDL3_image::SDL3_image glm::glm)