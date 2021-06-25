#pragma once
#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <dlfcn.h>
#endif
#include <glm/glm.hpp>

#include "../../../resources/Bots/BotInterface.hpp"

#ifdef _WIN32
typedef BotInterface* (__cdecl* NewInterface)();
#elif __linux__
typedef BotInterface* (*NewInterface)();
#endif

class BotLoader {
public:
	BotLoader(std::string botName);
	virtual ~BotLoader();

	// ----DLL functions----
	NewInterface newInterface;
	// ---------------------

	// ----Getters----
	bool isLoaded() const;
	// ---------------

	// ----Setters----
	void loadDLL();
	void unloadDLL();
	void reloadDLL();
	// ---------------

private:

	void* m_handle;
	bool m_loaded;
	std::string m_botName;
};
