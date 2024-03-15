#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "common_function.h"
#include "base_object.h"

class PlayerObject : public base_object
{
    public:
    PlayerObject();
    ~PlayerObject();

    enum MoveType
    {
        MOVE_RIGHT_ = 0,
        MOVE_LEFT_ = 1,
    };

    bool LoadImage ( std::string path, SDL_Renderer* screen);
    void Show ( SDL_Renderer* des );
    void HandleInputAction (SDL_Event events, SDL_Renderer* screen);
    void set_clips();

    private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;
};


#endif