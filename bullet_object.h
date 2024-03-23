#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H

#include "base_object.h"
#include "common_function.h"

class bullet_object : public base_object
{
public:
    bullet_object();
    ~bullet_object();

    enum BULLET_DIR
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

    void bullet_handle_move(const int& x_limit_screen, const int& y_limit_screen);
private:
    int x_val_;
    int y_val_;
    bool is_move_;
    int bullet_dir;
};

#endif