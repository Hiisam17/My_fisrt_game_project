#include "common_function.h"
#include "base_object.h"
#include "threats.h"

#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 5

ThreatsObject::ThreatsObject()
{
    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    frame_ = 0;
    comeback_time_ = 0;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;

    animation_a_ = 0;
    animation_b_ = 0;
    input_type_.left_ = 1;
    type_move_ = STATIC_THREATS;
    flip = false;
}

ThreatsObject::~ThreatsObject()
{
Free();
}

bool ThreatsObject::LoadImage(std::string path, SDL_Renderer* screen, bool flip)
{
    bool ret = base_object::LoadImage(path, screen, false);
    if (ret == true)
    {
        width_frame_ = rect_.w / 8;
        height_frame_ = rect_.h;
    }
    return ret;
}

void ThreatsObject::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = height_frame_;

        frame_clip_[1].x = width_frame_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = width_frame_;
        frame_clip_[1].h = height_frame_;

        frame_clip_[2].x = 2 * width_frame_;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = width_frame_;
        frame_clip_[2].h = height_frame_;

        frame_clip_[3].x = 3 * width_frame_;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = width_frame_;
        frame_clip_[3].h = height_frame_;

        frame_clip_[4].x = 4 * width_frame_;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = width_frame_;
        frame_clip_[4].h = height_frame_;

        frame_clip_[5].x = 5 * width_frame_;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = width_frame_;
        frame_clip_[5].h = height_frame_;

        frame_clip_[6].x = 6 * width_frame_;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = width_frame_;
        frame_clip_[6].h = height_frame_;

        frame_clip_[7].x = 7 * width_frame_;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = width_frame_;
        frame_clip_[7].h = height_frame_;
    }
}

void ThreatsObject::Show(SDL_Renderer* des)
{
    if (comeback_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if (frame_ >= 8)
        {
            frame_ = 0;
        }
        SDL_Rect* current_clip = &frame_clip_[frame_];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0.0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
}

void ThreatsObject::DoPlayer(Map& g_map)
{
    if (comeback_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += THREAT_GRAVITY_SPEED;
        if (y_val_ >= THREAT_MAX_FALL_SPEED)
        {
            y_val_ = THREAT_MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }
        else if (input_type_.right_ == 1)
        {
            x_val_ += THREAT_SPEED;
        }

        CheckToMap(g_map);
    }
    else if (comeback_time_ > 0)
    {
        comeback_time_--;
        if (comeback_time_ == 0)
        {
            x_val_ = 0;
            y_val_ = 0;
            if (x_pos_ > 256)
            {
                x_pos_ -= 256;
                animation_a_ -= 256;
                animation_b_ -= 256;
            }
            else
            {
                x_pos_ = 0;
            }
            y_pos_ = 0;
            comeback_time_ = 0;
        }
    }
}

void ThreatsObject::CheckToMap(Map& g_map)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int height_min_ = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    //Kiểm tra va chạm
    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 10) / TILE_SIZE; // -1 là sai số 

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min_ - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // go right
        {
            if (g_map.tile[y1][x2] != BLANK_TILE || g_map.tile[y2][x2] != BLANK_TILE)
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }
        }
        else if (x_val_ < 0)
        {
            if (g_map.tile[y1][x1] != BLANK_TILE || g_map.tile[y2][x1] != BLANK_TILE)
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min - 10) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0) // go down
        {
            if (g_map.tile[y2][x1] != BLANK_TILE || g_map.tile[y2][x2] != BLANK_TILE)
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                on_ground = true;
            }
        }
        else if (y_val_ < 0)
        {
            if (g_map.tile[y1][x1] != BLANK_TILE || g_map.tile[y1][x2] != BLANK_TILE)
            {
                y_pos_ = y1 * TILE_SIZE;
                y_pos_ += (height_frame_ + 2);
                y_val_ = 0;
                on_ground = false;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0) 
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > g_map.max_x_)
    {
        x_pos_ = g_map.max_x_ - width_frame_ - 1;
    }
}

void ThreatsObject::ImpMoveType (SDL_Renderer* screen, SDL_RendererFlip flip_)
{
    if (type_move_ == STATIC_THREATS)
    {
        ;
    }
    else if (type_move_ == MOVE_IN_SPACE_THREATS)
    {
        if (on_ground == true)
        {
            if (x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                flip = false;
                flip_ = SDL_FLIP_NONE;
                LoadImage("img//walk_left.jpg", screen, false);
            }
            else if (x_pos_ < animation_a_)
            {
                input_type_.left_ = 0;
                input_type_.right_ = 1;
                flip_ = SDL_FLIP_HORIZONTAL;
                flip = true;
                LoadImage("img//walk_left.jpg", screen, true);
            }   
        }
        else
        {
            if (input_type_.left_ == 1)
            {
                flip_ = SDL_FLIP_NONE;
                flip = false;
                LoadImage("img//walk_left.jpg", screen, false);
            }
            else
            {
                flip_ = SDL_FLIP_HORIZONTAL;
                flip = true;
                LoadImage("img//walk_left.jpg", screen, true);
            }
        }
    }
}