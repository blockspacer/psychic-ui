#include <iostream>
#include "demo.hpp"
#include "example/demo/DemoWindow.hpp"
#include <psychic-ui/Application.hpp>

using namespace psychic_ui;

int main(int /* argc */, char ** /* argv */) {
    try {
        auto app = std::make_unique<Application>();
        app->init();
        app->open(std::make_shared<DemoWindow>());
        app->mainloop();
        app->shutdown();
    } catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << std::endl;
        return -1;
    }

    return 0;
}
