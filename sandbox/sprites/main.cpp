#define INCLUDE_SDL
#include <cmath>
#include <iostream>
#include "Engine.hpp"
#include "Sprite.hpp"

// get time in between frames
// this is essential to ensure that a fast CPU won't make your game fast
// and a slow CPU won't make it slow
float deltaTime();

int main() {
    Engine& engine = Engine::instance();
    engine.createWindow("Jack's Sweet Sandbox", 1200, 800, WindowOptionBits::eResizeable);

    Sprite sprite("assets/Dungeon_Asset_Pack/character and tileset/Dungeon_Character.png", SDL_FRect{4, 3, 16, 16});
    sprite.setPosition(100, 100);
    sprite.scaleBy(10);

    float speed = 0.4f;
    float g = 0.0f;
    bool jumping = true;

    while(!engine.shouldClose()) {
        engine.pollEvents();
        engine.clear();

        float dt = deltaTime();
        float screenHeight = engine.windowHeight() - 100 - sprite.height();

        if (engine.getKeyState(SDL_SCANCODE_W) && !jumping) {
            jumping = true;
            g = -0.5f;
        }
        if (engine.getKeyState(SDL_SCANCODE_A)) {
            sprite.moveLeft(speed * dt);
            if (!sprite.isFlipped())
                sprite.flip();
        }
        if (engine.getKeyState(SDL_SCANCODE_D)) {
            sprite.moveRight(speed * dt);
            if (sprite.isFlipped())
                sprite.flip();
        }

        if (sprite.positionY() <= screenHeight && jumping) {
            sprite.setPositionY(sprite.positionY() + g * dt);
            g += 0.001 * dt;
        } else {
            sprite.setPositionY(screenHeight);
            jumping = false;
        }

        sprite.draw();
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