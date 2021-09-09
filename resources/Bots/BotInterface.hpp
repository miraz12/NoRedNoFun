#pragma once

#include <iostream>

#define BOT_EXPORTS

#ifdef _WIN32
	#ifdef BOT_EXPORTS
	#define BOT_API __declspec(dllexport)
	#else
	#define BOT_API __declspec(dllimport)
	#endif
#endif

class BotInterface {
public:
	virtual void print() = 0;
	virtual void update(float dt) = 0;
	virtual void actionMove(void (*f)(unsigned int key, BotInterface* bot)) = 0;
	virtual void actionFire(void (*f)(BotInterface* bot)) = 0;

	unsigned int m_id = 0;
};

// ----DLL functions----
#ifdef _WIN32
extern "C" BOT_API BotInterface * newInterface(unsigned int id);
#elif __linux__
extern "C" BotInterface * newInterface(unsigned int id);
#endif
// ---------------------
