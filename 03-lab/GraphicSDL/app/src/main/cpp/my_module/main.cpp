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
        "SDL",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        200,                               // width, in pixels
        200,                               // height, in pixels
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

    SDL_Rect rect, darea;
    int row = 0,column = 0,x = 0;

    while (1) {
        // Set render color to red ( background will be rendered in this color )
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);

        // Clear winow
        SDL_RenderClear( renderer );

        /* Get the Size of drawing surface */
        SDL_RenderGetViewport(renderer, &darea);
        for( ; row < 8; row++)
        {
            column = row%2;
            x = column;
            for( ; column < 4+(row%2); column++)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

                rect.w = darea.w/8;
                rect.h = darea.h/8;
                rect.x = x * rect.w;
                rect.y = row * rect.h;
                x = x + 2;

                SDL_RenderFillRect(renderer, &rect);
            }
        }

        // Render the rect to the screen
        SDL_RenderPresent(renderer);
    }
}