#ifndef MENU_H
#define MENU_H
#include "common_function.h"
#include "base_object.h"

bool showMenu(SDL_Renderer* renderer, Uint32& start_time_, Mix_Music* g_sound_menu);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* ren);
bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);


#endif