#include "common_function.h"
#include "base_object.h"
#include "menu.h"

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* ren)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* loadedImage = IMG_Load(file.c_str());
    if (loadedImage != NULL)
    {
        SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage -> format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        if (texture == NULL)
        {
            std::cout << "Create texture from surface failed" << std::endl;
        }
    }
    else
    {
        std::cout << "Load image failed" << std::endl;
    }
    return texture;
}

void showMenu(SDL_Renderer* renderer) {
    // Load menu options
    SDL_Texture* g_menu[3];
    g_menu[0] = loadTexture("img//menu_play.jpg", renderer);
    g_menu[1] = loadTexture("img//menu_quit.jpg", renderer);
    g_menu[2] = loadTexture("img//menu_.jpg", renderer);

    // Define rectangles for menu options
    SDL_Rect menuRects[2];

    menuRects[0].x = 420;
    menuRects[0].y = 380;
    menuRects[0].w = 430;
    menuRects[0].h = 75;

    menuRects[1].x = 420;
    menuRects[1].y = 480;
    menuRects[1].w = 430;
    menuRects[1].h = 75;

    bool isRunning = true;
    int menu_index;
    int last_menu_index = 2;
    SDL_Event event;

    while (isRunning) {
        // Clear the screen
        SDL_RenderClear(renderer);

        // Render the menu options
        SDL_RenderCopy(renderer, g_menu[2], NULL, NULL);

        // Update the screen
        SDL_RenderPresent(renderer);

        // Handle events
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEMOTION) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                menu_index = -1;

                // Check if any menu option was clicked
                for (int i = 0; i < 2; i++) {
                    if (SDL_PointInRect(new SDL_Point{x, y}, &menuRects[i])) {
                        // Handle the click on the menu option
                        menu_index = i;
                        break;
                    }
                }
                
                if (menu_index != -1)
                {
                    SDL_RenderCopy(renderer, g_menu[menu_index], NULL, NULL);
                    SDL_RenderPresent(renderer);
                }
                else
                {
                    SDL_RenderCopy(renderer, g_menu[2], NULL, NULL);
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }

    // Clean up
    for (int i = 0; i < 3; i++) {
        SDL_DestroyTexture(g_menu[i]);
    }
}

bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect) {
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
        return true;
    }
    return false;
}