cmake_minimum_required(VERSION 3.10)

# set the project name
project(NoRedNoFun)

# Generate compile_commands.json for LSP
if (UNIX)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif(UNIX)
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
ADD_SUBDIRECTORY(exts)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_compile_options(${PROJECT_NAME} PUBLIC 
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:-Wall;-Wextra>
	$<$<CXX_COMPILER_ID:MSVC>:/W4>)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} exts)
target_compile_options(${PROJECT_NAME} PUBLIC 
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:>
	$<$<CXX_COMPILER_ID:MSVC>:>)
ADD_DEPENDENCIES(${PROJECT_NAME} exts)

# Copy resource folder to binary folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)

# Tell MSVC to run debug binary from folder with debug binary
if (MSVC)
	set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif(MSVC)
