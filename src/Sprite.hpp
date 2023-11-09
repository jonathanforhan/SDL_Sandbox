#pragma once
#include <string>
#include <cstdint>

/**
 * Sprite class holds only the x y w h data and the handle to a texture
 * imo it's weird to have all these floats but SDL can do sub-pixel transforms
 */
class Sprite {
public:
    Sprite(const std::string& path, float x, float y, float width, float height);

    // draw to buffer in queue, not presented yet
    void draw(float x, float y, float width, float height);

    // draw but fill screen
    void fill();

    float width() const { return m_width; }
    float height() const { return m_height; }

private:
    size_t m_textureIndex;
    float m_x;
    float m_y;
    float m_width;
    float m_height;
};