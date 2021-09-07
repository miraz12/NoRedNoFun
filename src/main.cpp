#include "Game/Window.hpp"

#include <iostream>
#include <exception>
#include <stdexcept>

void handle_eptr(std::exception_ptr eptr) {
    try {
        if (eptr) {
            std::rethrow_exception(eptr);
        }
    } catch(const std::exception& e) {
        std::cout << "Caught exception \"" << e.what() << "\"\n";
    }
}    

int main() {
    std::exception_ptr eptr;
    try {
        Window win;
        if (win.open()) {
            return win.gameLoop();
        }
        return -1;
    } catch(...) {
        eptr = std::current_exception();
    } 
    handle_eptr(eptr);    
}

