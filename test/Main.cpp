#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

int main()
{
    printf("hello world!\n");
    SDL_Window *window = 0;

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
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x0, 0xff);
    SDL_RenderDrawPoint(renderer, 100, 100);
    SDL_RenderPresent(renderer);

    bool quit = false;

    while (!quit)
    {
        SDL_Event e;

        if (SDL_PollEvent(&e))
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                ;
            }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

