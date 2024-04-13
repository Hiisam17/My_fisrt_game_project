#ifndef SLASH_SKILL_H
#define SLASH_SKILL_H

#include "common_function.h"
#include "base_object.h"
#include <vector>

class SlashSkill : public base_object
{
public:
    SlashSkill();
    ~SlashSkill();

    bool LoadImage(std::string path, SDL_Renderer* screen, bool flip_horizontal = false);
    void set_frame_width(const int& frameWidth) { frame_width_ = frameWidth; }
    void set_frame_height(const int& frameHeight) { frame_height_ = frameHeight; }
    int get_frame_width() const { return frame_width_; }
    int get_frame_height() const { return frame_height_; }
    void set_x_val(const float& xVal) { x_val_ = xVal; }
    void set_y_val(const float& yVal) { y_val_ = yVal; }
    void set_x_pos(const float& xp) { x_pos_ = xp; }
    void set_y_pos(const float& yp) { y_pos_ = yp; }
    void set_is_explosion(const bool& is_exp) { is_explosion_ = is_exp; }
    float get_x_pos() const { return x_pos_; }
    float get_y_pos() const { return y_pos_; }
    float get_x_val() const { return x_val_; }
    float get_y_val() const { return y_val_; }
    void Skill_Move(const int& x_border, const int& y_border);
    bool get_is_explosion() const { return is_explosion_; }
    
    void Show(SDL_Renderer* des, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void set_clip();


private:
    int frame_width_;
    int frame_height_;
    float x_pos_;
    float y_pos_;
    float x_val_;
    float y_val_;
    SDL_Rect frame_skill;
    bool is_explosion_;
};
#endif