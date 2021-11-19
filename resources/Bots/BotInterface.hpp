#pragma once

#include <iostream>
#include <vector>

#define BOT_EXPORTS

#ifdef _WIN32
	#ifdef BOT_EXPORTS
	#define BOT_API __declspec(dllexport)
	#else
	#define BOT_API __declspec(dllimport)
	#endif
#endif

enum EntityType {
	UNKNOWN,
	WEAPON
};

struct VisualEntity {
    float distance{0.0f};
	float directionX{1.0f};
	float directionY{1.0f};
    int entityHit{-1};
	EntityType type{EntityType::UNKNOWN};
};

class BotInterface {
public:
	virtual void print() = 0;
	virtual void update(float dt, std::vector<VisualEntity>* eyes) = 0;
	virtual void actionMove(void (*f)(unsigned int key, BotInterface* bot)) = 0;
	virtual void actionFire(void (*f)(BotInterface* bot)) = 0;
	virtual void actionLookAt(void (*f)(int x, int y, BotInterface* bot)) = 0;
	virtual void actionLookInDirection(void (*f)(float x, float y, BotInterface* bot)) = 0;

	unsigned int m_id{0};
};

// ----DLL functions----
#ifdef _WIN32
extern "C" BOT_API BotInterface * newInterface(unsigned int id);
#elif __linux__
extern "C" BotInterface * newInterface(unsigned int id);
#endif
// ---------------------
