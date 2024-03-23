#include "bullet_object.h"

bullet_object::bullet_object()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_dir = 0;
}

bullet_object::~bullet_object()
{

}

void bullet_object::bullet_handle_move(const int& x_limit_screen, const int& y_limit_screen)
{
    if (bullet_dir == RIGHT_DIR)
    {
        rect_.x += x_val_;
        if (rect_.x > x_limit_screen)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir == LEFT_DIR)
    {
        rect_.x -= x_val_;
        if (rect_.x > x_limit_screen)
        {
            is_move_ = false;
        }
    }

}