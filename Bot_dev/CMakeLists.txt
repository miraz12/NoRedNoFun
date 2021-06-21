# CMakeList.txt : CMake project for Bot, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project(myBot)

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


# Copy resource folder to binary folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_BINARY_DIR}/libmyBot.so"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/Bots)
