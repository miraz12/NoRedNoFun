#pragma once
#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <dlfcn.h>
#endif
#include <glm/glm.hpp>

#include "../../../resources/Bots/BotInterface.hpp"

typedef BotInterface* (__cdecl* NewInterface)();

class BotLoader {
public:
	BotLoader(std::string botName);
	virtual ~BotLoader();

	// ----DLL functions----
	NewInterface newInterface = NULL;
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
	HINSTANCE m_handle;
	bool m_loaded;
	std::string m_botName;
};