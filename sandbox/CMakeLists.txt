# this is how we copy the images from assets to each child project in the sandbox
# just add this dependency in the child directory
add_custom_target(COPY_ASSETS
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/assets"
		"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")

# just add a CMakeLists.txt to a directory and call SANDBOX_PROJECT() and you have a new sandbox exe
function(SANDBOX_PROJECT)
	file(GLOB_RECURSE C_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
	file(GLOB_RECURSE CXX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

	get_filename_component(DIRNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
	add_executable(${DIRNAME})

	if (MSVC)
		set_target_properties(${DIRNAME} PROPERTIES COMPILE_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
	else ()
		set_target_properties(${DIRNAME} PROPERTIES COMPILE_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
	endif ()

	target_sources(${DIRNAME} PUBLIC ${C_SOURCES} ${CXX_SOURCES})
	target_include_directories(${DIRNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
	target_link_libraries(${DIRNAME} PUBLIC SDL_ENGINE)
	add_dependencies(${DIRNAME} COPY_ASSETS)
endfunction()

file(GLOB V_GLOB LIST_DIRECTORIES true "*")
foreach(ITEM ${V_GLOB})
	get_filename_component(FILENAME ${ITEM} NAME)
	if(IS_DIRECTORY ${ITEM} AND NOT ${FILENAME} STREQUAL "assets")
		add_subdirectory(${ITEM})
	endif()
endforeach()