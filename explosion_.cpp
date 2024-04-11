#include "common_function.h"
#include "explosion_.h"
#include "base_object.h"

ExplosionObject::ExplosionObject()
{
    frame_ = 0;
    frame_width_ = 0;
    frame_height_ = 0;
    is_explosion_ = false;
}

ExplosionObject::~ExplosionObject()
{
    ;
}

bool ExplosionObject::LoadImage(std::string path, SDL_Renderer* screen)
{
    bool ret = base_object::LoadImage(path, screen);
    if (ret == true)
    {
        frame_width_ = rect_.w / 8;
        frame_height_ = rect_.h;
    }
    return ret;
}

void ExplosionObject::set_clip()
{
    if (frame_width_ > 0 && frame_height_ > 0)
    {
        clip_[0].x = 0;
        clip_[0].y = 0;
        clip_[0].w = frame_width_;
        clip_[0].h = frame_height_;

        clip_[1].x = frame_width_;
        clip_[1].y = 0;
        clip_[1].w = frame_width_;
        clip_[1].h = frame_height_;

        clip_[2].x = 2 * frame_width_;
        clip_[2].y = 0;
        clip_[2].w = frame_width_;
        clip_[2].h = frame_height_;

        clip_[3].x = 3 * frame_width_;
        clip_[3].y = 0;
        clip_[3].w = frame_width_;
        clip_[3].h = frame_height_;

        clip_[4].x = 4 * frame_width_;
        clip_[4].y = 0;
        clip_[4].w = frame_width_;
        clip_[4].h = frame_height_;

        clip_[5].x = 5 * frame_width_;
        clip_[5].y = 0;
        clip_[5].w = frame_width_;
        clip_[5].h = frame_height_;

        clip_[6].x = 6 * frame_width_;
        clip_[6].y = 0;
        clip_[6].w = frame_width_;
        clip_[6].h = frame_height_;

        clip_[7].x = 7 * frame_width_;
        clip_[7].y = 0;
        clip_[7].w = frame_width_;
        clip_[7].h = frame_height_;
    }
}

void ExplosionObject::Show(SDL_Renderer* des)
{
    if (frame_ >= 8)
    {
        frame_ = 0;
    }
    SDL_Rect* current_clip = &clip_[frame_];
    SDL_Rect renderQuad = { rect_.x, rect_.y, frame_width_, frame_height_ };
    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}