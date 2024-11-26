#include <iostream>
#include "core/Application.hpp"

int main() {
    try {
        Application app;
        app.run();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
