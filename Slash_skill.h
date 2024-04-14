#ifndef SLASH_SKILL_H
#define SLASH_SKILL_H

#include "common_function.h"
#include "base_object.h"
#include <vector>

class slash_skill_object : public base_object
{
public:
    slash_skill_object();
    ~slash_skill_object();

    enum SKILL_DIR
    {
        RIGHT_DIR = 10,
        LEFT_DIR = 11,
    };

    void set_x_val(const int& xVal) {x_val_ = xVal;}
    void set_y_val(const int& yVal) {y_val_ = yVal;}
    void set_is_move(const bool& isMove) {is_move_ = isMove;}

    int get_x_val() {return x_val_;}
    int get_y_val() {return y_val_;}
    bool get_is_move() {return is_move_;}

    void slash_skill_handle_move(const int& x_limit_screen, const int& y_limit_screen);

    void set_skill_dir(const unsigned int& dir) {skill_dir = dir;}
    unsigned int get_skill_dir() {return skill_dir;}

    SDL_Rect get_skill_box(SDL_Rect skill_box) {skill_box.x = x_pos_; skill_box.y = y_pos_; skill_box.w = width_frame_; skill_box.h = height_frame_; return skill_box;}

    void set_x_pos(const int& xp) {x_pos_ = xp;}
    void set_y_pos(const int& yp) {y_pos_ = yp;}
    void set_width_frame(const int& width) {width_frame_ = width;}
    void set_height_frame(const int& height) {height_frame_ = height;}

    int get_width_frame() {return width_frame_;}
    int get_height_frame() {return height_frame_;}

private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int skill_dir;
    SDL_Rect skill_box;

    int x_pos_;
    int y_pos_;
    int width_frame_;
    int height_frame_;
};

#endif