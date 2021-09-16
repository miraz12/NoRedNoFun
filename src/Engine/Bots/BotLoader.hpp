#pragma once
#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <dlfcn.h>
#endif
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "../../../resources/Bots/BotInterface.hpp"

#ifdef _WIN32
typedef BotInterface* (__cdecl* NewInterface)(unsigned int);
#elif __linux__
typedef BotInterface* (*NewInterface)(unsigned int);
#endif


class BotLoader {
public:

struct botInstance {
	BotInterface* bot;
	unsigned int m_id;
	void* m_handle;
	bool m_loaded{false};
	std::string m_botName;
	};

	BotLoader() = delete;
	BotLoader(GLFWwindow* window);
	virtual ~BotLoader();

	// ----DLL functions----
	std::vector<botInstance*> m_bots;
	// ---------------------

	// ----Getters----
	bool isLoaded() const;
	// ---------------

	// ----Setters----
	void loadDLL(std::string botName);
	void unloadDLL();
	void reloadDLL();
private:
	GLFWwindow* win;
	void setupBotActions(botInstance* botIns);

};
