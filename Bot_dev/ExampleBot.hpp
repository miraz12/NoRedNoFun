
#include "../resources/Bots/BotInterface.hpp"

class ExampleBot : public BotInterface {
    public:
    ExampleBot() = default;
    ExampleBot(unsigned int id) { m_id = id; };
    ~ExampleBot() = default;

    void update(float dt, std::vector<VisualEntity>* eyes) override;
    void print() override; 
    
	void actionMove(void (*f)(unsigned int key, BotInterface* bot)) override {moveFunc = f;};
	void actionFire(void (*f)(BotInterface* bot)) override {fireFunc = f;};
	void actionLookAt(void (*f)(int x, int y, BotInterface* bot)) override { lookFunc = f;};
	void actionLookInDirection(void (*f)(float x, float y, BotInterface* bot)) override { lookInDirectionFunc = f;};
private:
	void (*moveFunc)(unsigned int, BotInterface*);
	void (*fireFunc)(BotInterface*);
	void (*lookFunc)(int, int, BotInterface*);
	void (*lookInDirectionFunc)(float, float, BotInterface*);
};

#ifdef _WIN32
BOT_API BotInterface* newInterface(unsigned int id) {
	return new ExampleBot(id); //Client needs to delete this
}
#elif __linux__
BotInterface* newInterface(unsigned int id) {
	return new ExampleBot(id); //Client needs to delete this
}
#endif


