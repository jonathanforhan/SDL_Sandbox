#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <cstdint>
#include <string_view>
#include <unordered_map>
#include <vector>

// These match the SDL spec for ease of use
using WindowOptions = uint32_t;
enum WindowOptionBits : WindowOptions {
    eFullscreen = 0x01,
    eBorderless = 0x10,
    eResizeable = 0x20,
    eMinimized = 0x40,
    eMaximized = 0x80,
};

/**
 * Engine contains the Window and Renderer for the SDL_ENGINE
 * Engine is a singleton (https://betterprogramming.pub/what-is-a-singleton-2dc38ca08e92)
 * being a singleton means it can hold global application state that we can reference from anywhere
 */
class Engine {
private:
    // private constructor
    Engine();

public:
    // Engine is non-copyable
    Engine(const Engine&) = delete;
    void operator=(const Engine&) = delete;

    ~Engine();

    // get the singleton instance
    static Engine& instance();

    // create the SDL window (and renderer)
    void createWindow(std::string_view title, uint32_t width = 1200, uint32_t height = 800, WindowOptions opts = NULL);

    // this is optional you can poll events yourself if you choose
    SDL_Event pollEvents(bool doChecks = true);

    // clear color buffer
    void clear();

    // swap buffers
    void present();

    // shouldClose will get changed on poll events if QUIT event is caught
    bool shouldClose() const { return m_shouldClose; }
    void setShouldClose(bool b = true) { m_shouldClose = b; }

    // for texture tracking
    bool hasTexture(const std::string& path) const { return m_textures.count(path); }
    SDL_Texture* textureAt(const std::string& path) { return m_textures.at(path); }
    SDL_Texture* addTexture(const std::string& path);
    void removeTexture(const std::string& path);

    uint8_t getKeyState(uint32_t key) const { return m_keystate[key]; }

    int32_t windowWidth() const;
    int32_t windowHeight() const;
    std::tuple<int32_t, int32_t> windowDimensions() const;

    SDL_Renderer* renderer() { return m_renderer; }
    SDL_Window* window() { return m_window; }

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
    std::unordered_map<std::string, SDL_Texture*> m_textures;
    const uint8_t* m_keystate;

    bool m_shouldClose{false};
};
