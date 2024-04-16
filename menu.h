#ifndef MENU_H
#define MENU_H
#include "common_function.h"
#include "base_object.h"

void showMenu(SDL_Renderer* renderer);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* ren);
bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);


#endif