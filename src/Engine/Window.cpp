#include "Window.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <glad/glad.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include "Rendering.hpp"
#include "Game/Game.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void errorCallback(int /*error*/, const char* description) { printf("Error: %s\n", description); }

GLFWwindow* window;

bool Window::open() {
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
   ImGui_ImplOpenGL3_Init("#version 130");

   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
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
      Rendering::getInstance().update((float) dt);

      // render
      // ------
      Rendering::getInstance().draw();

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
   static int counter = 0;

   ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

   ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

   ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

   if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
   counter++;
   ImGui::SameLine();
   ImGui::Text("counter = %d", counter);

   ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
   ImGui::End();
   // Rendering
   ImGui::Render();
}