#include "../resources/Bots/BotInterface.hpp"

BotInterface::BotInterface() {

}

BotInterface::~BotInterface() {

}

void BotInterface::print() {
	std::cout << "Bot interface\n";
}

BOT_API BotInterface* newInterface() {
	return new BotInterface(); //Client needs to delete this
}