#include "Engine.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdexcept>
#include <iostream>

Engine::Engine() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    m_keystate = SDL_GetKeyboardState(NULL);
}

Engine::~Engine() {
    // cleanup

    for (auto& texture : m_textures) {
        SDL_DestroyTexture(texture.second);
    }
    
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

Engine& Engine::instance() {
    // static instance lives the life of program
    static Engine s_instance;
    return s_instance;
}

void Engine::createWindow(std::string_view title, uint32_t width, uint32_t height, WindowOptions opts) {
    m_window = SDL_CreateWindow(title.data(), width, height, SDL_WINDOW_HIGH_PIXEL_DENSITY | opts);
    if (m_window == nullptr) {
        throw std::runtime_error("SDL_CreateWindow failure");
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        SDL_DestroyWindow(m_window);
        throw std::runtime_error("SDL_CreateRenderer failure");
    }
}

SDL_Event Engine::pollEvents(bool doChecks) {
    SDL_Event e;
    SDL_PollEvent(&e);

    m_keystate = SDL_GetKeyboardState(NULL);

    if (!doChecks) {
        return e;
    }

    switch (e.type) {
        case SDL_EVENT_QUIT:
            m_shouldClose = true;
            break;
    }

    return e;
}

void Engine::clear() {
    SDL_RenderClear(m_renderer);
}

void Engine::present() {
    SDL_RenderPresent(m_renderer);
}

SDL_Texture* Engine::addTexture(const std::string& path) {
    if (hasTexture(path)) {
        throw std::runtime_error("Trying to add a duplicate texture");
    }

    // make our image surface
    SDL_Surface* img = IMG_Load(path.data());
    if (img == NULL) {
        throw std::runtime_error("SDL_Surface nullptr exception");
    }

    // construct a new texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, img);
    m_textures.emplace(path, texture);

    SDL_DestroySurface(img);

    return texture;
}

void Engine::removeTexture(const std::string& textureName) {
    if (!m_textures.count(textureName)) {
        return;
    }
    m_textures.erase(m_textures.find(textureName));
}

int32_t Engine::windowWidth() const {
    int w;
    SDL_GetWindowSize(m_window, &w, nullptr);
    return w;
}

int32_t Engine::windowHeight() const {
    int h;
    SDL_GetWindowSize(m_window, nullptr, &h);
    return h;
}

std::tuple<int32_t, int32_t> Engine::windowDimensions() const {
    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    return {w, h};
}
