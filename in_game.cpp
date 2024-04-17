#include "common_function.h"
#include "base_object.h"
#include "in_game.h"

PlayerMoney::PlayerMoney()
{
    x_pos_ = 0;
    y_pos_ = 0;
}

PlayerMoney::~PlayerMoney()
{
}

void PlayerMoney::InitMoney(SDL_Renderer* screen)
{
    bool ret = LoadImage("map//4.png", screen, false);

}

void PlayerMoney::Show(SDL_Renderer* des)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    Render(des);
}

void Geometric::RenderRectangle(const GeometricFormat& geo_size, SDL_Renderer* screen, const ColorData& color_data)
{
    SDL_Rect fillRect = {geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_};
    SDL_SetRenderDrawColor(screen, color_data.red_, color_data.green_, color_data.blue_, 0xFF);
    SDL_RenderFillRect(screen, &fillRect);
}

void Geometric::RenderOutline(const GeometricFormat& geo_size, SDL_Renderer* screen, const ColorData& color_data)
{
    SDL_Rect outlineRect = {geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_};
    SDL_SetRenderDrawColor(screen, color_data.red_, color_data.green_, color_data.blue_, 0xFF);
    SDL_RenderDrawRect(screen, &outlineRect);
}