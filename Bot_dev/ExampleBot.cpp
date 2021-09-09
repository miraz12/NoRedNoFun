#include "ExampleBot.hpp"

unsigned int currKey = 3; // Example logic remove
float timer = 0.0f;
void ExampleBot::update(float dt) {
    moveFunc(currKey, this);
	fireFunc(this);
	timer += dt;
	if (timer > 1.0f) {
		if(currKey != 3) {
			currKey++;
		} else {
			currKey = 0;
		}
		timer = 0.0f;
	}
}
void ExampleBot::print() {
    std::cout << "Bot interface\n";
}
