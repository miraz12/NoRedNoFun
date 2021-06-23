#pragma once

#include <iostream>

#define BOT_EXPORTS

#ifdef BOT_EXPORTS
#define BOT_API __declspec(dllexport)
#else
#define BOT_API __declspec(dllimport)
#endif

class BotInterface {
public:
	BotInterface();
	virtual ~BotInterface();

	virtual void print();

private:
};

// ----DLL functions----
extern "C" BOT_API BotInterface * newInterface();
// ---------------------
