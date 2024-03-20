#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "common_function.h"
#include "base_object.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 20
#define JUMP_SPEED 20
#define CURRENT_HEIGHT 6

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

    void action_player( Map& map_data);
    float get_x_val_() {return x_val_;}
    void check_action_player(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
    void lock_map_to_character(Map& map_data);

    bool is_game_over(Map& map_data);

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
    bool on_ground;

    int map_x_;
    int map_y_;

};


#endif