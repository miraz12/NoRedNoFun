#include "BotLoader.h"

#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

BotLoader::BotLoader() {
	std::string botPath = "resources/Bots";
	for(const auto & entry : fs::directory_iterator(botPath)) {
		std::string fileName{entry.path().filename().string()};

#ifdef _WIN32
		if(fileName.find(".dll") != std::string::npos) {
#elif __linux__
		if(fileName.find(".so") != std::string::npos) {
#endif
			std::cout << entry.path().filename() << std::endl;
			loadDLL(fileName);
		}
	}
}

BotLoader::~BotLoader() {
	unloadDLL();
}

void BotLoader::loadDLL(std::string botName) {
	// Load dll
	NewInterface newInterface;
	botInstance* newBot = new botInstance();
	m_bots.push_back(newBot);

#ifdef _WIN32
	newBot->m_handle = LoadLibrary(("resources/Bots/" + botName).c_str());
#elif __linux__
	newBot->m_handle = dlopen(("resources/Bots/lib" + botName).c_str(), RTLD_LAZY);
#endif
	if (newBot->m_handle != NULL) {
		// Function pointers
#ifdef _WIN32
		newInterface = (NewInterface)GetProcAddress((HMODULE)newBot->m_handle, "newInterface");
#elif __linux__
		newInterface = (NewInterface)dlsym(newBot->m_handle, "newInterface");
#endif
		newBot->m_loaded = true;

		// Catch failed function loads
		if (newInterface == nullptr) {
			std::cout << "Failed to load function \"newInterface\" from bot \"" << newBot->m_botName.c_str() << "\".\n";
			newBot->m_loaded = false;
		}
		newBot->bot = newInterface(m_bots.size());

	}
	else {
		std::cout << "Failed to load bot \"" << newBot->m_botName.c_str() << "\".\n";
		newBot->m_loaded = false;
	}
}

void BotLoader::unloadDLL() {
	for(botInstance* b : m_bots) {
#ifdef _WIN32
		FreeLibrary((HMODULE)b->m_handle);
#elif __linux__
	dlclose(b->m_handle);
#endif
		b->m_loaded = false;
	}
}

void BotLoader::reloadDLL() {
	for(botInstance* b : m_bots) {
		unloadDLL();
		loadDLL(b->m_botName);
	}
}

bool BotLoader::isLoaded() const {
	return true; // TODO ???
}
