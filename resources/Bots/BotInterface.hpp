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
	BotInterface();
	virtual ~BotInterface();

	virtual void print();
	virtual void update(unsigned int& command);

private:
};

// ----DLL functions----
#ifdef _WIN32
extern "C" BOT_API BotInterface * newInterface();
#elif __linux__
extern "C" BotInterface * newInterface();
#endif
// ---------------------
