#include "Sprite.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdexcept>
#include "Engine.hpp"

Sprite::Sprite(const std::string& path, float x, float y, float width, float height)
    : m_x(x),
      m_y(y),
      m_width(width),
      m_height(height) {

    Engine& engine = Engine::instance();

    if (!engine.hasTexture(path)) {
        m_textureIndex = engine.addTexture(path);
    } else {
        m_textureIndex = engine.indexOfTexture(path);
    }
}

void Sprite::draw(float x, float y, float width, float height) {
    Engine& engine = Engine::instance();
    SDL_FRect src = {m_x, m_y, m_width, m_height};
    SDL_FRect dst = {x, y, width, height};
    SDL_RenderTexture(Engine::instance().renderer(), engine.textureAt(m_textureIndex), &src, &dst);
}

void Sprite::fill() {
    Engine& engine = Engine::instance();
    SDL_FRect src = {m_x, m_y, m_width, m_height};
    SDL_RenderTexture(Engine::instance().renderer(), engine.textureAt(m_textureIndex), &src, nullptr);
}
