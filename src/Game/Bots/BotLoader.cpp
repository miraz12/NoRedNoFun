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
		newInterface = (NewInterface)GetProcAddress(m_handle, "newInterface");

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
	FreeLibrary(m_handle);
	m_loaded = false;
}

void BotLoader::reloadDLL() {
	unloadDLL();
	loadDLL();
}

bool BotLoader::isLoaded() const {
	return m_loaded;
}
