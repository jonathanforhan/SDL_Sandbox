#pragma once
#include <string>
#include <cstdint>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

/**
 * Sprite class holds only the x y w h data and the handle to a texture
 * imo it's weird to have all these floats but SDL can do sub-pixel transforms
 */
class Sprite {
public:
    Sprite(const std::string& path, SDL_FRect bounds);

    // draw to buffer in queue, not presented yet
    void draw();

    // draw but fill screen
    void fill();

    float width() const { return m_state.w; }
    float height() const { return m_state.h; }
    void scaleBy(float magnitude) {
        m_state.w = m_bounds.w * magnitude;
        m_state.h = m_bounds.h * magnitude;
    }
    void scaleX(float x) { m_state.w = m_bounds.w * x; }
    void scaleY(float y) { m_state.h = m_bounds.h * y; }

    float positionX() const { return m_state.x; }
    float positionY() const { return m_state.y; }
    void setPositionX(float x) { m_state.x = x; }
    void setPositionY(float y) { m_state.y = y; }
    void setPosition(float x, float y) {
        m_state.x = x;
        m_state.y = y;
    }

    void moveUp(float magnitude);
    void moveDown(float magnitude);
    void moveLeft(float magnitude);
    void moveRight(float magnitude);

    void flip() {
        m_flip = m_flip & SDL_FLIP_HORIZONTAL ? m_flip = SDL_FLIP_NONE : m_flip = SDL_FLIP_HORIZONTAL;
    }
    bool isFlipped() { return m_flip == SDL_FLIP_HORIZONTAL; }

private:
    SDL_Texture* m_texturePtr;
    SDL_FRect m_bounds;
    SDL_FRect m_state;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;
};