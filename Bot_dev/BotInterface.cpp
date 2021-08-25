#include "../resources/Bots/BotInterface.hpp"

BotInterface::BotInterface() {

}

BotInterface::~BotInterface() {

}

unsigned int currKey = 3;
unsigned int iter = 0;
void BotInterface::update(unsigned int& command) {
	command = currKey;
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

void BotInterface::print() {
	std::cout << "Bot interface\n";
}

#ifdef _WIN32
BOT_API BotInterface* newInterface() {
	return new BotInterface(); //Client needs to delete this
}
#elif __linux__
BotInterface* newInterface() {
	return new BotInterface(); //Client needs to delete this
}
#endif
