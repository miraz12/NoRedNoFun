#include "BotLoader.h"


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
	m_handle = LoadLibrary(("resources/Bots/" + m_botName + ".dll").c_str());

	if (m_handle != NULL) {
		// Function pointers
#ifdef _WIN32
		newInterface = (NewInterface)GetProcAddress((HMODULE)m_handle, "newInterface");
#elif __linux__
		newInterface = (NewInterface)dlsym(m_handle, "newInterface");
#endif
		m_loaded = true;

		// Catch failed function loads
		if (newInterface == NULL) {
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
