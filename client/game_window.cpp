#include "game_window.h"

GameWindow::GameWindow(int width, int height)
    : screen_width(width), screen_height(height) {
    if (SDL_Init(SDL_INIT_VIDEO))
        throw SdlException("Error en la inicialización", SDL_GetError());

    if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
                                    &window, &renderer))
        throw SdlException("Error al crear ventana", SDL_GetError());

    chargeGraphics();
}

void GameWindow::chargeGraphics() {
    texturas.push_back(new Texture());
    texturas.at(0)->loadTexture((std::string)PATH_HUMAN, renderer);
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

Texture* GameWindow::getTexture() {
  return texturas.at(0);
}