#include "ExampleBot.hpp"

unsigned int currKey = 3; // Example logic remove
float timer = 0.0f;
void ExampleBot::update(float dt, std::vector<VisualEntity>* eyes) {
    moveFunc(currKey, this);
	fireFunc(this);
	lookInDirectionFunc(-1.0f, 0.0f, this);
	timer += dt;
//	printf("Number of collisions: %d\n", (*eyes).size());
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
