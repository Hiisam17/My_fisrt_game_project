#include "common_function.h"
#include "base_object.h"
#include "Slash_skill.h"

SlashSkill::SlashSkill()
{
    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    frame_width_ = 0;
    frame_height_ = 0;
    is_explosion_ = false;
}

SlashSkill::~SlashSkill()
{
}

void SlashSkill::set_clip()
{
    frame_skill.x = 0;
    frame_skill.y = 0;
    frame_skill.w = frame_width_;
    frame_skill.h = frame_height_;
}

bool SlashSkill::LoadImage(std::string path, SDL_Renderer* screen, bool flip_horizontal)
{
    bool ret = base_object::LoadImage(path, screen, flip_horizontal);
    if (ret == true)
    {
        frame_width_ = rect_.w;
        frame_height_ = rect_.h;
    }
    return ret;
}

void SlashSkill::Skill_Move(const int& x_border, const int& y_border)
{
    x_pos_ += x_val_;
    if (x_pos_ > x_border)
    {
        is_explosion_ = true;
    }
}

void SlashSkill::Show(SDL_Renderer* des, SDL_RendererFlip flip)
{
    flip = SDL_FLIP_NONE;
    LoadImage("img//Slash_skill.png", des, false);
    rect_.x = x_pos_;
    rect_.y = y_pos_;

    SDL_Rect* current_clip = &frame_skill;

    SDL_Rect renderQuad = {rect_.x, rect_.y, frame_width_, frame_height_};

    SDL_RenderCopyEx (des, p_object_, current_clip, &renderQuad, 0, NULL, flip);
}

