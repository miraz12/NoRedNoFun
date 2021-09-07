#include "Game/Window.hpp"

int main() {
    Window win;
    if (win.open()) {
        return win.gameLoop();
    }
    return -1;
}

