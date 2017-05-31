/**
 * Note: this code has been taken from https://github.com/stephen47/android-sdl2-gradle-template
 */


#include "SDL.h"
#include <stdio.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "SDL Mouse Tracker",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            640,                               // width, in pixels
            480,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())
    // Setup renderer
    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        // In the case that the window could not be made...
        printf("Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    while (1) {
        // Set render color to red ( background will be rendered in this color )
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);

        // Clear winow
        SDL_RenderClear( renderer );

        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                case SDL_KEYDOWN:
                case SDL_FINGERDOWN:
                case SDL_FINGERMOTION:
                    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255);

                    SDL_Rect rect;
                    rect.x = (int)event.tfinger.x;
                    rect.y = (int)event.tfinger.y;
                    rect.w = 100;
                    rect.h = 100;

                    SDL_RenderFillRect(renderer, &rect);
                    break;
            }
        }

        // Render the rect to the screen
        SDL_RenderPresent(renderer);
    }
}
