#include "BotLoader.h"

//#include <dlfcn.h>
#include <iostream>

BotLoader::BotLoader(std::string botName) {
	m_loaded = false;
	m_botName = botName;
	loadDLL();
}

BotLoader::~BotLoader() {
	unloadDLL();
}

void BotLoader::loadDLL() {
	// Load dll

#ifdef _WIN32
	m_handle = LoadLibrary(("resources/Bots/" + m_botName + ".dll").c_str());
#elif __linux__
	m_handle = dlopen(("resources/Bots/lib" + m_botName + ".so").c_str(), RTLD_LAZY);
#endif
	if (m_handle != NULL) {
		// Function pointers
#ifdef _WIN32
		newInterface = (NewInterface)GetProcAddress((HMODULE)m_handle, "newInterface");
#elif __linux__
		newInterface = (NewInterface)dlsym(m_handle, "newInterface");
#endif
		m_loaded = true;

		// Catch failed function loads
		if (newInterface == nullptr) {
			std::cout << "Failed to load function \"newInterface\" from bot \"" << m_botName << "\".\n";
			m_loaded = false;
		}
	}
	else {
		std::cout << "Failed to load bot \"" << m_botName << "\".\n";
		m_loaded = false;
	}
}

void BotLoader::unloadDLL() {
#ifdef _WIN32
	FreeLibrary((HMODULE)m_handle);
#elif __linux__
	dlclose(m_handle);
#endif
	m_loaded = false;
}

void BotLoader::reloadDLL() {
	unloadDLL();
	loadDLL();
}

bool BotLoader::isLoaded() const {
	return m_loaded;
}
