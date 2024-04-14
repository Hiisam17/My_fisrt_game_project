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
private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int skill_dir;
};

#endif