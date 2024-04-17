#ifndef IN_GAME_H
#define IN_GAME_H

#include "common_function.h"
#include "base_object.h"

class PlayerMoney : public base_object
{
    public:
    PlayerMoney();
    ~PlayerMoney();

    void InitMoney(SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void SetPos(const int& xPos, const int& yPos) {x_pos_ = xPos; y_pos_ = yPos;}

    private:
    int x_pos_;
    int y_pos_;
};

struct GeometricFormat
{
    public:
    GeometricFormat(int left, int top, int width, int height) : left_(left), top_(top), width_(width), height_(height) {}

    int left_;
    int top_;
    int width_;
    int height_;

};

struct ColorData
{
    public:
    ColorData(Uint8 red, Uint8 green, Uint8 blue) : red_(red), green_(green), blue_(blue) {}

    Uint8 red_;
    Uint8 green_;
    Uint8 blue_;
};

class Geometric
{
    public:
    static void RenderRectangle(const GeometricFormat& geo_size, SDL_Renderer* screen, const ColorData& color_data);
    static void RenderOutline(const GeometricFormat& geo_size, SDL_Renderer* screen, const ColorData& color_data);
};

#endif