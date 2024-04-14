#include "common_function.h"
#include "base_object.h"
#include "Slash_skill.h"



slash_skill_object::slash_skill_object()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    skill_dir = 0;

    x_pos_ = 0;
    y_pos_ = 0;
    width_frame_ = 64;
    height_frame_ = 64;
}


slash_skill_object::~slash_skill_object()
{

}

void slash_skill_object::slash_skill_handle_move(const int& x_limit_screen, const int& y_limit_screen)
{
    if (skill_dir == RIGHT_DIR)
    {
        rect_.x += x_val_;
        if (rect_.x > x_limit_screen)
        {
            is_move_ = false;
        }
    }
    else if (skill_dir == LEFT_DIR)
    {
        rect_.x -= x_val_;
        if (rect_.x < -x_limit_screen)
        {
            is_move_ = false;
        }
    }

}
