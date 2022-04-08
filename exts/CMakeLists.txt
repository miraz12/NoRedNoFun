ADD_LIBRARY(exts INTERFACE)

# OpenGL
find_package(OpenGL REQUIRED)

# GLAD
add_library(glad STATIC glad/src/glad.c glad/include/glad/glad.h)
TARGET_INCLUDE_DIRECTORIES(glad PUBLIC glad/include)


# GLFW
#ADD_SUBDIRECTORY(glfw)
#SET_TARGET_PROPERTIES(glfw PROPERTIES FOLDER "exts/glfw")
#TARGET_INCLUDE_DIRECTORIES(exts SYSTEM INTERFACE glfw/include)

SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
SET(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
SET(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
SET(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")		  


# GLM
ADD_SUBDIRECTORY(glm)
TARGET_INCLUDE_DIRECTORIES(exts SYSTEM INTERFACE glm/include)

# OpenAL 
# No OpenAL for web
#add_subdirectory(openal-soft)

# IMGUI 
ADD_LIBRARY(imgui STATIC  imgui/imgui.cpp 
                          imgui/imgui_demo.cpp
                          imgui/imgui_draw.cpp
                          imgui/imgui_internal.h
                          imgui/imgui_tables.cpp
                          imgui/imgui_widgets.cpp
                          imgui/imstb_rectpack.h
                          imgui/imstb_textedit.h
                          imgui/imstb_truetype.h
                          imgui/backends/imgui_impl_glfw.h
                          imgui/backends/imgui_impl_glfw.cpp
                          imgui/backends/imgui_impl_opengl3.h
                          imgui/backends/imgui_impl_opengl3.cpp)
TARGET_INCLUDE_DIRECTORIES(imgui PUBLIC imgui glfw/include)

# STB_IMAGE
TARGET_INCLUDE_DIRECTORIES(exts SYSTEM INTERFACE stb_image)

if (WIN32)
    TARGET_LINK_LIBRARIES(exts INTERFACE opengl32 glad glm imgui)
elseif(UNIX)
  TARGET_LINK_LIBRARIES(exts INTERFACE GL glad glm dl imgui)
endif()
