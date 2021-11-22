cmake_minimum_required(VERSION 3.10)

# set the project name
project(NoRedNoFun)

# Generate compile_commands.json for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Add source files
file(GLOB_RECURSE GAME_FILES
	${CMAKE_SOURCE_DIR}/src/Game/*.cpp
	${CMAKE_SOURCE_DIR}/src/Game/*.hpp)
# Add external libs
add_subdirectory(exts)
add_subdirectory(Bot_dev)
add_subdirectory(src/Engine)
add_subdirectory(src/Game)

# Creaty executable
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC Engine Game)
if(UNIX)
target_link_libraries(${PROJECT_NAME} PUBLIC stdc++fs stdc++fs)
endif(UNIX)

# Make executale dependant on libs
add_dependencies(${PROJECT_NAME} Engine Game)

# Copy resource folder to binary folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources DEPENDS myBot)

# Tell MSVC to run debug binary from folder with debug binary
if (MSVC)
	set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif(MSVC)
