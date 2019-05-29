#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

int main()
{
    printf("hello world!\n");
    SDL_Window *window = 0;
    SDL_Surface *surface = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw "could not initialize SD2";
    if (!(window = SDL_CreateWindow
        ( "Hello World!"
        , SDL_WINDOWPOS_UNDEFINED
        , SDL_WINDOWPOS_UNDEFINED
	    , SCREEN_WIDTH
        , SCREEN_HEIGHT
        , SDL_WINDOW_SHOWN
        )))
        throw "could not create window";
    surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, 0, SDL_MapRGB(surface->format, 0xff, 0xff, 0x00));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

