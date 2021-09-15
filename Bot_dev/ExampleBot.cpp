#include "ExampleBot.hpp"

unsigned int currKey = 3; // Example logic remove
float timer = 0.0f;
void ExampleBot::update(float* dt) {
	while (true) {
		moveFunc(currKey, this);
		//fireFunc(this);
		//lookFunc(0, 0, this);
		timer += 0.01f;
		if (timer > 1.0f) {
			if(currKey != 3) {
				currKey++;
			} else {
				currKey = 0;
			}
			timer = 0.0f;
		}
	}
}
void ExampleBot::print() {
    std::cout << "Bot interface\n";
}
