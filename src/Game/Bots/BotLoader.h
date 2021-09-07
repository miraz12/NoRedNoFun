#pragma once
#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <dlfcn.h>
#endif
#include <glm/glm.hpp>
#include <vector>

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
	void* m_handle;
	bool m_loaded{false};
	std::string m_botName;
	};

	BotLoader();
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
};
