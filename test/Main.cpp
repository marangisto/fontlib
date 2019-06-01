#include <stdio.h>
#include <SDL2/SDL.h>
#include <fontlib.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

using namespace fontlib;

static void draw_glyph(SDL_Renderer *renderer, font_t& font, char ch)
{
    int x0 = SCREEN_WIDTH / 2 - font.height / 4;
    int y0 = SCREEN_HEIGHT / 2 + font.height / 2;

    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
    SDL_RenderClear(renderer);

    SDL_Texture *texture = SDL_CreateTexture
        ( renderer
        , SDL_PIXELFORMAT_RGB888
        , SDL_TEXTUREACCESS_TARGET
        , SCREEN_WIDTH
        , SCREEN_HEIGHT
        );

    SDL_SetRenderTarget(renderer, texture);

    const glyph_t *g = get_glyph(font, ch);

    if (g)
    {
        printf("%d %d %d %d\n", g->width, g->height, g->offset_h, g->offset_v);
        SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xff);
        SDL_RenderDrawLine(renderer, x0, 0, x0, SCREEN_HEIGHT -1);
        SDL_RenderDrawLine(renderer, 0, y0, SCREEN_WIDTH -1, y0);
        SDL_RenderDrawLine(renderer, 0, y0 + font.min_y, SCREEN_WIDTH -1, y0 + font.min_y);
        SDL_RenderDrawLine(renderer, 0, y0 + font.max_y, SCREEN_WIDTH -1, y0 + font.max_y);
        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0xff, 0xff);
        SDL_Rect outer = { x0-1, y0 + font.max_y + 1, g->width+2, -(font.height+2) };
        SDL_RenderDrawRect(renderer, &outer);
        SDL_SetRenderDrawColor(renderer, 0xff, 0x0, 0x0, 0xff);
        SDL_Rect inner = { x0 + g->offset_h, y0 + g->offset_v, g->width, g->height };
        SDL_RenderDrawRect(renderer, &inner);
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x0, 0xff);
        SDL_RenderDrawLine(renderer, x0 + g->offset_h, y0 + font.min_y, x0 + g->offset_h + g->width - 1, y0 + font.min_y);
        SDL_RenderDrawLine(renderer, x0 + g->offset_h, y0 + font.max_y, x0 + g->offset_h + g->width - 1, y0 + font.max_y);

        for (unsigned r = 0; r < g->height; ++r)
        {
            for (unsigned c = 0; c < g->width; ++c)
            {
                unsigned color = g->bitmap[r * g->width + c];
                SDL_SetRenderDrawColor(renderer, color, color, color, 0xff);
                SDL_RenderDrawPoint(renderer, x0 + g->offset_h + c, y0 + g->offset_v + r);
            }
        }
    }

    SDL_SetRenderTarget(renderer, 0);
    SDL_RenderCopy(renderer, texture, 0, 0);

    SDL_RenderPresent(renderer);
}

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
	    , SCREEN_WIDTH * 4
        , SCREEN_HEIGHT * 4
        , SDL_WINDOW_SHOWN
        )))
        throw "could not create window";

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x0, 0xff);
    SDL_RenderPresent(renderer);

    bool quit = false;
    font_t font = fontlib::cmunrm_48;

    SDL_StartTextInput();

    while (!quit)
    {
        SDL_Event e;

        if (SDL_PollEvent(&e))
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_TEXTINPUT:
                {
                    uint16_t uc = e.text.text[0];

                    if (uc < 0x80)
                        draw_glyph(renderer, font, (char) uc);
                }
                break;
            default:
                ;
            }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

