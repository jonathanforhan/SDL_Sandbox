#include "Engine.hpp"
#include "Sprite.hpp"

int main() {
    Engine& engine = Engine::instance();
    engine.createWindow("Jack's Sweet Sandbox", 1100, 700, WindowOptionBits::eResizeable);

    Sprite sprite("assets/hello_world/hello_world.png", 0, 0, 1099, 690);

    while(!engine.shouldClose()) {
        engine.pollEvents();
        engine.clear();
        sprite.fill();
        engine.present();
    }
}