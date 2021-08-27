#include "ExampleBot.hpp"

unsigned int currKey = 3; // Example logic remove
unsigned int iter = 0;
void ExampleBot::update() {
    outPutFunc(currKey);
	iter++;
	if (iter > 30) {
		if(currKey != 3) {
			currKey++;
		} else {
			currKey = 0;
		}
		iter = 0;
	}
}
void ExampleBot::print() {
    std::cout << "Bot interface\n";
}
