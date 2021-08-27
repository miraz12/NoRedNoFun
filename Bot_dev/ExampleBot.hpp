
#include "../resources/Bots/BotInterface.hpp"

class ExampleBot : public BotInterface {
    public:
    ExampleBot() = default;
    ~ExampleBot() = default;

    void update() override;
    void print() override; 
    
	void output(void (*f)(unsigned int key)) override {outPutFunc = f;};
    
private:
	void (*outPutFunc)(unsigned int);
};

#ifdef _WIN32
BOT_API BotInterface* newInterface() {
	return new ExampleBot(); //Client needs to delete this
}
#elif __linux__
BotInterface* newInterface() {
	return new ExampleBot(); //Client needs to delete this
}
#endif


