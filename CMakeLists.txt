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
add_subdirectory(src/Engine)
add_subdirectory(src/Game)

# Creaty executable
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC Engine Game)

# Make executale dependant on libs
add_dependencies(${PROJECT_NAME} Engine Game)

if(NOT DEFINED IS_JENKINS)
# Copy resource folder to binary folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources DEPENDS myBot)
if (EMSCRIPTEN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()
endif()

# Tell MSVC to run debug binary from folder with debug binary
if (MSVC)
	set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif(MSVC)
