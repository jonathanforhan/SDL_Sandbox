#define INCLUDE_SDL
#include <cmath>
#include "Engine.hpp"
#include "Sprite.hpp"

// get time in between frames
float deltaTime();

int main() {
    Engine& engine = Engine::instance();
    engine.createWindow("Jack's Sweet Sandbox", 1200, 800, WindowOptionBits::eResizeable);

    Sprite sprite("assets/Dungeon_Asset_Pack/character and tileset/Dungeon_Character.png", 0, 0, 16, 16);

    float timeSinceStart = 0;

    while(!engine.shouldClose()) {
        timeSinceStart += deltaTime();
        float x = 100 * cos(timeSinceStart / 1000) + engine.windowWidth() / 2 - 50;
        float y = 100 * sin(timeSinceStart / 1000) + engine.windowHeight() / 2 - 50;
        engine.pollEvents();
        engine.clear();
        sprite.draw(x, y, 100.0f, 100.0f);
        engine.present();
    }
}

float deltaTime() {
    static uint64_t prev = SDL_GetTicks();
    uint64_t now = SDL_GetTicks();

    float dt = static_cast<float>(now) - static_cast<float>(prev);

    prev = now;
    return dt;
}