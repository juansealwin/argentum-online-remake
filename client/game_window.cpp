#include "game_window.h"

GameWindow::GameWindow(int width, int height)
    : screen_width(width), screen_height(height) {
        window = SDL_CreateWindow("Argentum", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN);

    if (!window)
        throw SdlException("Error en la inicialización de la ventana",
                           SDL_GetError());
    else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
            throw SdlException("Error en la inicialización del render",
                               SDL_GetError());
        else
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    chargeGraphics();
}

void GameWindow::chargeGraphics() {
    texturas.push_back(new Texture());
    texturas.push_back(new Texture());
    texturas.at(0)->loadTexture((std::string)PATH_HUMAN_BODY, renderer);
    texturas.at(1)->loadTexture((std::string)PATH_HUMAN_HEAD, renderer);
}

GameWindow::~GameWindow() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void GameWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

void GameWindow::fill() { fill(0x33, 0x33, 0x33, 0xFF); }

void GameWindow::render() { SDL_RenderPresent(renderer); }

SDL_Renderer* GameWindow::getRenderer() { return renderer; }

Texture* GameWindow::getTexture(int index) { return texturas.at(index); }