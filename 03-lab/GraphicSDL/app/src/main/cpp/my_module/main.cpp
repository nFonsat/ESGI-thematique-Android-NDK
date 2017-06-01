/**
 * Note: this code has been taken from https://github.com/stephen47/android-sdl2-gradle-template
 */


#include "SDL.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "SDL Chess",                  // window title
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

    int width, heigth;

    SDL_GetWindowSize(window, &width, &heigth);

    int sizeSquarre=width/5;

    while (1) {
        // Set render color to red ( background will be rendered in this color )

        // Clear winow
        SDL_RenderClear( renderer );

        for(int ligne = 0; ligne < 6; ligne++) {
            for(int column = 0; column < 7; column ++) {
                if(column % 2 == 0) {
                    if(ligne % 2 == 0) {
                        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);
                        SDL_Rect rect = (SDL_Rect){ligne * sizeSquarre, column * sizeSquarre, sizeSquarre, sizeSquarre};
                        SDL_RenderFillRect(renderer, &rect);
                    }
                } else {
                    if(ligne % 2 != 0) {
                        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
                        SDL_Rect rect = (SDL_Rect){ligne * sizeSquarre, column * sizeSquarre, sizeSquarre, sizeSquarre};
                        SDL_RenderFillRect(renderer, &rect);
                    }
                }

            }
        }

        // Render the rect to the screen
        SDL_RenderPresent(renderer);
    }
}