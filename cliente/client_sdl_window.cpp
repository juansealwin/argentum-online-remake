#include "client_sdl_window.h"

SdlWindow::SdlWindow(int width, int height) : screen_width(width), 
                                              screen_height(height) {
    if(!SDL_Init(SDL_INIT_VIDEO))
        throw SdlException("Error en la inicialización", SDL_GetError());
    
    window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN );
    
    if(!window)
        throw SdlException("Error al crear la ventana", SDL_GetError());
    else
        //Get window surface
        screen_surface = SDL_GetWindowSurface(window);
    
    /*if(SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
        &window, &renderer))
        throw SdlException("Error al crear ventana", SDL_GetError());*/
}

SdlWindow::~SdlWindow() {
    /*if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }*/
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

/*void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

void SdlWindow::fill() {
    fill(0x33,0x33,0x33,0xFF);
}*/

void SdlWindow::loadImage(){

	//Load splash image
	screen_surface = SDL_LoadBMP(PATH_IMG_LOBBY);
	if(!screen_surface )
        throw SdlException("Unable to load image", SDL_GetError());

}

void SdlWindow::blitSurfaceAndUpadate() {
        //Apply the image
    SDL_BlitSurface( screen_surface, NULL, screen_surfaceb, NULL );
    
    //Update the surface
    SDL_UpdateWindowSurface(window);

    //Wait two seconds
    SDL_Delay( 2000 );
}
