# CMakeList.txt : CMake project for Bot, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project(myBot)
if (UNIX)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif(UNIX)

# Add source files
set(SOURCE_FILES 
	"dllmain.cpp"
	"BotInterface.cpp"
	)
	
# Add header files
set(HEADER_FILES 
	"../resources/Bots/BotInterface.hpp"
	"framework.hpp"
	)

# Add source to this project's executable.
add_library (${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
