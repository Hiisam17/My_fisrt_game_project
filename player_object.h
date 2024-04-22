#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "common_function.h"
#include <vector>
#include "base_object.h"
#include "Slash_skill.h"


#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 10
#define JUMP_SPEED 20
#define CURRENT_HEIGHT 6
#define GOAL_POINT 5
#define MONEY_COIN 4
#define INJURED 1

class PlayerObject : public base_object
{
    public:
    PlayerObject();
    ~PlayerObject();

    enum MoveType
    {
        MOVE_RIGHT_ = 0,
        MOVE_LEFT_ = 1,
        JUMP_UP_ = 2,
        ATTACK_ = 3,
        SPECIAL_ATTACK_ = 4,
    };

    bool LoadImage ( std::string path, SDL_Renderer* screen, bool flip_horizontal = false);
    bool LoadImage_Attack (std::string path, SDL_Renderer* screen, bool flip_horizontal);
    void Show ( SDL_Renderer* des, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Show_Attack ( SDL_Renderer* des, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void HandleInputAction (SDL_Event events, SDL_Renderer* screen, Mix_Chunk* g_sound_sword[2]);
    void set_clips();

    void action_player( Map& map_data);
    float get_x_val_() {return x_val_;}
    void check_action_player(Map& map_data, Mix_Chunk* g_sound_coin);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
    void lock_map_to_character(Map& map_data);

    bool is_game_over(Map& map_data, PlayerObject& player);

    bool is_win(Map& map_data, PlayerObject& player);

    int get_status() {return status_;}

    SDL_Rect get_player_box(SDL_Rect player_box) {player_box.x = int (x_pos_); player_box.y = int (y_pos_); player_box.w = width_frame_; player_box.h = height_frame_; return player_box;}

    bool get_attack() {return status_ == ATTACK_;}
    bool get_injured() {return true;}

    void set_skill_list(const std::vector<slash_skill_object*> &skill_list);

    std::vector<slash_skill_object*> get_skill_list() const {return skill_list_;}

    void HandleSkill(SDL_Renderer* des);
    void RemoveSkill(const int& skill_num, std::vector<slash_skill_object*> &skill_list);

    void earn_money(Mix_Chunk* g_sound_coin) {Mix_PlayChannel(-1, g_sound_coin, 0); money_count ++;}
    int get_money() {return money_count;}

    int get_width_frame() {return width_frame_;}
    int get_height_frame() {return height_frame_;}

    int get_mark() {return score_count;}
    void set_mark(const int& mark) {score_count += mark;}

    private:

    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int temp_x_left;
    int temp_y_left;
    int temp_x_right;
    int temp_y_right;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground;

    int map_x_;
    int map_y_;

    std::vector<slash_skill_object*> skill_list_;

    bool end_skill;

    int money_count;

    int score_count;

};


#endif