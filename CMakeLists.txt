cmake_minimum_required(VERSION 3.10)

# set the project name
project(NoRedNoFun)

# Generate compile_commands.json for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source files
file(GLOB_RECURSE ENGINE_FILES
	${CMAKE_SOURCE_DIR}/src/Engine/*.cpp
	${CMAKE_SOURCE_DIR}/src/Engine/*.hpp)

# Add source files
file(GLOB_RECURSE GAME_FILES
	${CMAKE_SOURCE_DIR}/src/Game/*.cpp
	${CMAKE_SOURCE_DIR}/src/Game/*.hpp)
# Add external libs
add_subdirectory(exts)
add_subdirectory(Bot_dev)

# Add source files as libraries
add_library(Engine ${ENGINE_FILES})
target_include_directories(Engine SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src/Engine ${CMAKE_SOURCE_DIR}/src/)
target_link_libraries(Engine PUBLIC exts)
target_compile_options(Engine PRIVATE 
						$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
     			       -Wall -pedantic -Werror>
						$<$<CXX_COMPILER_ID:MSVC>:
						/W4;/WX>)  
set_target_properties(Engine PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CMAKE_CXX_EXTENSIONS OFF)
target_compile_definitions(Engine PUBLIC GLM_FORCE_SILENT_WARNINGS=1)

# Add source files as libraries
add_library(Game ${GAME_FILES})
target_include_directories(Game SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src/Game ${CMAKE_SOURCE_DIR}/src/)
target_link_libraries(Game PUBLIC exts)
target_compile_options(Game PRIVATE 
						$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
     			       -Wall -pedantic -Werror>
						$<$<CXX_COMPILER_ID:MSVC>:
						/W4;/WX>)
set_target_properties(Game PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CMAKE_CXX_EXTENSIONS OFF)
target_compile_definitions(Game PUBLIC GLM_FORCE_SILENT_WARNINGS=1)

# Creaty executable
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC Engine Game)
if(UNIX)
target_link_libraries(${PROJECT_NAME} PUBLIC stdc++fs)
endif(UNIX)

# Make executale dependant on libs
add_dependencies(${PROJECT_NAME} Engine Game)

# Copy resource folder to binary folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)

# Tell MSVC to run debug binary from folder with debug binary
if (MSVC)
	set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif(MSVC)
