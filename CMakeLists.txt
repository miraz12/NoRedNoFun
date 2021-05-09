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
	${CMAKE_SOURCE_DIR}/src/*.hpp)

ADD_SUBDIRECTORY(exts)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})



TARGET_LINK_LIBRARIES(${PROJECT_NAME} exts)
ADD_DEPENDENCIES(${PROJECT_NAME} exts)

