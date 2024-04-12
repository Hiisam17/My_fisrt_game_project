#include "base_object.h"
#include "common_function.h"
#include "base_func.h"

bool InitData() 
{
    bool success = true;

    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");


    g_window = SDL_CreateWindow("CONTRA GAME - GAME_CODING_PRACTICE",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, 
                                 SCREEN_WIDTH, SCREEN_HEIGHT, 
                                 SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        success = false;
    }
    else
    {

        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
        {
            success = false;
        }
        else 
        {

            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                success = false;
            }
        }
    }

    return success;
}

bool LoadBackground(base_object& g_background)
{

    bool ret = g_background.LoadImage("img//background.png", g_screen, false);
    if (ret == false) 
    {
        return false;
    }
    return true;
}

void close(base_object& g_background) 
{

    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}