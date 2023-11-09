#include "Sprite.hpp"
#include <stdexcept>
#include "Engine.hpp"

Sprite::Sprite(const std::string& path, SDL_FRect bounds)
    : m_texturePtr(nullptr),
      m_bounds({}),
      m_state({0.0f, 0.0f, bounds.w, bounds.h}) {

    m_bounds.x = bounds.x * m_state.w;
    m_bounds.y = bounds.y * m_state.h;
    m_bounds.w = bounds.w;
    m_bounds.h = bounds.h;

    Engine& engine = Engine::instance();

    if (!engine.hasTexture(path)) {
        m_texturePtr = engine.addTexture(path);
    } else {
        m_texturePtr = engine.textureAt(path);
    }
}

void Sprite::draw() {
    SDL_RenderTextureRotated(Engine::instance().renderer(), m_texturePtr, &m_bounds, &m_state, 0, NULL, m_flip);
}

void Sprite::fill() {
    SDL_RenderTexture(Engine::instance().renderer(), m_texturePtr, &m_bounds, nullptr);
}

void Sprite::moveUp(float magnitude) {
    m_state.y -= magnitude;
}

void Sprite::moveDown(float magnitude) {
    m_state.y += magnitude;
}

void Sprite::moveLeft(float magnitude) {
    m_state.x -= magnitude;
}

void Sprite::moveRight(float magnitude) {
    m_state.x += magnitude;
}
