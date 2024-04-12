#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "common_function.h"
#include "base_object.h"

class ExplosionObject : public base_object
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void set_clip();
    void set_frame(const int& fr) { frame_ = fr; }
    bool LoadImage(std::string path, SDL_Renderer* screen, bool flip_horizontal = false);
    int get_frame_width() const { return frame_width_; }
    int get_frame_height() const { return frame_height_; }
    void set_frame_width(const int& fw) { frame_width_ = fw; }
    void set_frame_height(const int& fh) { frame_height_ = fh; }
    void set_is_explosion(const bool& is_exp) { is_explosion_ = is_exp; }
    void set_x_pos(const int& xp) { rect_.x = xp; }
    void set_y_pos(const int& yp) { rect_.y = yp; }
    SDL_Rect get_rect_frame() const { return rect_; }

    void Show(SDL_Renderer* des);

private:
    int frame_width_;
    int frame_height_;
    unsigned int frame_;
    SDL_Rect clip_[8];

    bool is_explosion_;
};

#endif