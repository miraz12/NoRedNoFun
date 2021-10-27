cmake_minimum_required(VERSION 3.16)

# Add source files
file(GLOB_RECURSE ENGINE_FILES
	${CMAKE_SOURCE_DIR}/src/Engine/*.cpp
	${CMAKE_SOURCE_DIR}/src/Engine/*.hpp)

# Add source files as libraries
add_library(Engine ${ENGINE_FILES})
target_include_directories(Engine SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src/Engine ${CMAKE_SOURCE_DIR}/src/)
target_link_libraries(Engine PUBLIC exts)
target_compile_options(Engine PRIVATE 
						$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
     			       -Wall -pedantic -Werror>
						$<$<CXX_COMPILER_ID:MSVC>:
						/W3;>)  
set_target_properties(Engine PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CMAKE_CXX_EXTENSIONS OFF)
target_compile_definitions(Engine PUBLIC GLM_FORCE_SILENT_WARNINGS=1)
target_precompile_headers(Engine PRIVATE pch.h)
