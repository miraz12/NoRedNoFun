cmake_minimum_required(VERSION 3.10)

# set the project name
project(NoRedNoFun)

# Generate compile_commands.json for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp
	${CMAKE_SOURCE_DIR}/resources/Bots/BotInterface.hpp)

# Add external libs
add_subdirectory(exts)
add_subdirectory(Bot_dev)

# Creaty executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CMAKE_CXX_EXTENSIONS OFF)
# Link libraries
target_link_libraries(${PROJECT_NAME} exts myBot)
if(UNIX)
target_link_libraries(${PROJECT_NAME} stdc++fs)
endif(UNIX)
# Make executale dependant on libs
add_dependencies(${PROJECT_NAME} exts)

# Copy resource folder to binary folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)

# Tell MSVC to run debug binary from folder with debug binary
if (MSVC)
	set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif(MSVC)
