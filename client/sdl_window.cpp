#include "sdl_window.h"

SdlWindow::SdlWindow(int width, int height)
    : screen_width(width), screen_height(height) {
    if (SDL_Init(SDL_INIT_VIDEO))
        throw SdlException("Error en la inicialización", SDL_GetError());

    if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
                                    &window, &renderer))
        throw SdlException("Error al crear ventana", SDL_GetError());
}

SdlWindow::~SdlWindow() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

void SdlWindow::fill() { fill(0x33, 0x33, 0x33, 0xFF); }

void SdlWindow::render() { SDL_RenderPresent(renderer); }

SDL_Renderer* SdlWindow::getRenderer() { return renderer; }