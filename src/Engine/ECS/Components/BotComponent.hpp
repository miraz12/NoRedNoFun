#pragma once 
#include "Component.hpp"
#include "../../../../resources/Bots/BotInterface.hpp"

#include <vector>

enum aType{
	move,
	attack,
	lookAt
};
struct payload {
	payload() = default;
	unsigned int key;
	unsigned int x, y;
};
struct action {
	aType type{};
	payload data;
};


class BotComponent : public Component {

std::vector<action> actions;

public: 

    BotComponent();

    void addAction(action a);
	std::vector<action>& getActions();
    
};