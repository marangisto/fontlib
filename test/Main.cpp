#include <stdio.h>
#include <SDL.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

int main()
{
    printf("hello world!\n");
    SDL_Window *window = 0;
    SDL_Surface *surface = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw "could not initialize SD2";
}

