#include "Engine.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdexcept>
#include <iostream>

Engine::Engine() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

Engine::~Engine() {
    // cleanup

    for (auto texture : m_textures) {
        SDL_DestroyTexture(texture);
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

void Engine::pollEvents() {
    SDL_Event e;
    SDL_PollEvent(&e);

    switch (e.type) {
        case SDL_EVENT_QUIT:
            m_shouldClose = true;
            break;
    }
}

void Engine::clear() {
    SDL_RenderClear(m_renderer);
}

void Engine::present() {
    SDL_RenderPresent(m_renderer);
}

size_t Engine::addTexture(const std::string& path) {
    if (hasTexture(path)) {
        throw std::runtime_error("Trying to add a duplicate texture");
    }

    // make our image surface
    SDL_Surface* img = IMG_Load(path.data());
    if (img == NULL) {
        throw std::runtime_error("SDL_Surface nullptr exception");
    }

    // construct a new texture
    m_textures.emplace_back(SDL_CreateTextureFromSurface(m_renderer, img));
    SDL_DestroySurface(img);
    if (m_textures.back() == NULL) {
        throw std::runtime_error("SDL_RenderTexture nullptr exception");
    }

    //--- TODO check for null textures and fill them before blindly appending

    // add the index to our tracker
    size_t index = m_textures.size() - 1;
    m_texture_map.emplace(path, index);
    return index;
}

void Engine::removeTexture(const std::string& textureName) {
    if (!m_texture_map.count(textureName)) {
        return;
    }
    m_textures[m_texture_map.at(textureName)] = nullptr;
    m_texture_map.erase(m_texture_map.find(textureName));
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
