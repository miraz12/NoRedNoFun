#include "Window.hpp"

#ifdef _WIN32
#include <windows.h>
#include <errhandlingapi.h>
#endif

#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include "Game/Game.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void errorCallback(int /*error*/, const char* description) { printf("Error: %s\n", description); }

GLFWwindow* window;

bool isBigEndian()
{
    int a = 1;
    return !((char*)&a)[0];
}

int convertToInt(char* buffer, int len)
{
    int a = 0;
    if (!isBigEndian())
        for (int i = 0; i<len; i++)
            ((char*)&a)[i] = buffer[i];
    else
        for (int i = 0; i<len; i++)
            ((char*)&a)[3 - i] = buffer[i];
    return a;
}

char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
    char buffer[4];
    std::ifstream in(fn, std::ios::binary);
    in.read(buffer, 4);
    if (strncmp(buffer, "RIFF", 4) != 0)
    {
        std::cout << "this is not a valid WAVE file" << std::endl;
        return NULL;
    }
    in.read(buffer, 4);
    in.read(buffer, 4);      //WAVE
    in.read(buffer, 4);      //fmt
    in.read(buffer, 4);      //16
    in.read(buffer, 2);      //1
    in.read(buffer, 2);
    chan = convertToInt(buffer, 2);
    in.read(buffer, 4);
    samplerate = convertToInt(buffer, 4);
    in.read(buffer, 4);
    in.read(buffer, 2);
    in.read(buffer, 2);
    bps = convertToInt(buffer, 2);
    in.read(buffer, 4);      //data
    in.read(buffer, 4);
    size = convertToInt(buffer, 4);
    char* data = new char[size];
    in.read(data, size);
    return data;
}


bool Window::open() {
   glfwInit();
   glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
   glfwWindowHint(GLFW_SAMPLES, 4);

   glfwSetErrorCallback(errorCallback);
   SCR_WIDTH = 1000;
   SCR_HEIGHT = 1000;
   window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
   if (window == NULL)
   {
       std::cout << "Failed to create GLFW window" << std::endl;
       glfwTerminate();
       return false;
   }
   glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   glfwSwapInterval(0);


   //Setup IMGUI
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO(); (void)io;

   // Setup Dear ImGui style
   ImGui::StyleColorsDark();

   // Setup Platform/Renderer backends
   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init("#version 320 es");

   if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
   {
       std::cout << "Failed to initialize GLAD" << std::endl;
       return false;
   }

   return true;
}

bool Window::gameLoop() {
	currentTime = glfwGetTime();
	previousTime = currentTime;

	Game game(window);

   // render loop
   // -----------
   while (!glfwWindowShouldClose(window)) {
      // input
      // -----
      glfwPollEvents();
      processInput(window);

      renderImgui();
      
      // Update
      // -----
      currentTime = glfwGetTime();
      dt = currentTime - previousTime;
      previousTime = currentTime;

      if (fpsUpdateTimer <= fpsUpdate) {
         fpsUpdateTimer += (float) dt;
         tempFps += (1 / (float) dt);
         counter++;
      }
      else {
         fps = tempFps / counter;
         tempFps = 0.0f;
         counter = 0;
         fpsUpdateTimer = 0.0f;
         //std::cout << fps;
         glfwSetWindowTitle(window, ("OpenGL FPS: " + std::to_string((int)fps)).c_str());
      }

      updateTimer += dt;
      updatesSinceRender = 0;

      // If dt is bigger than minUpdateRate - update multiple times
      while (updateTimer >= minUpdateRate) { 
      if (updatesSinceRender >= 20) {
               // Too many updates, throw away the rest of dt (makes the game run in slow-motion)
         updateTimer = 0.0f;
         break;
      }

         game.update((float) minUpdateRate);
         updateTimer -= minUpdateRate;
         updatesSinceRender++;
      }

      if (updatesSinceRender == 0) { // dt is faster than 
         game.update((float) updateTimer);
         updateTimer = 0.0f;
      }

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      glfwSwapBuffers(window);
   }

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();

   glfwDestroyWindow(window);
   glfwTerminate();
   return true;
}

void processInput(GLFWwindow *theWindow)
{
    if(glfwGetKey(theWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(theWindow, true);
    }
}

void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height)
{
   SCR_WIDTH = width;
   SCR_HEIGHT = height;
   glViewport(0, 0, width, height);
}

void Window::renderImgui() {
   // Start the Dear ImGui frame
   ImGui_ImplOpenGL3_NewFrame();
   ImGui_ImplGlfw_NewFrame();
   ImGui::NewFrame();

   static float f = 0.0f;

   ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

   ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

   ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

   ImGui::End();
   // Rendering
   ImGui::Render();
}
