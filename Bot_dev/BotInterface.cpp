#include "../resources/Bots/BotInterface.hpp"

BotInterface::BotInterface() {

}

BotInterface::~BotInterface() {

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
