#include "common_function.h"
#include "base_object.h"
#include "player_object.h"
#include <algorithm>
#include "threats.h"
#include "Slash_skill.h"
#include <vector>


PlayerObject::PlayerObject()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.attack_ = 0;
    input_type_.jump_ = 0;
    input_type_.stand_left_ = 0;
    input_type_.stand_right_ = 0;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;
    hp_ = 3;
    dead_ = false;
}

PlayerObject::~PlayerObject()
{

}

bool PlayerObject::LoadImage (std::string path, SDL_Renderer* screen, bool flip_horizontal)
{
    bool ret = base_object::LoadImage (path, screen, flip_horizontal);

    if (ret == true)
    {
        width_frame_ = rect_.w / 8;
        height_frame_ = rect_.h;
    }

    return ret;
}

bool PlayerObject::LoadImage_Attack (std::string path, SDL_Renderer* screen, bool flip_horizontal)
{
    bool ret = base_object::LoadImage (path, screen, flip_horizontal);

    if (ret == true)
    {
        width_frame_ = rect_.w / 8 + 1;
        height_frame_ = rect_.h;
    }

    return ret;
}

void PlayerObject::set_clips()
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

void PlayerObject:: Show( SDL_Renderer* des, SDL_RendererFlip flip)
{
    if (status_ == MOVE_LEFT_ )
    {
        LoadImage( "img//run_left.jpg", des, false);
    }
    else if (status_ == MOVE_RIGHT_)
    {
        LoadImage ( "img//run_right.jpg", des, false);
    }
    /*else if (status_ == 0)
    {
        LoadImage ("img//stand_right.jpg", des);
        LoadImage ("img//stand_left.jpg", des);
    }*/

    if (input_type_.left_ == 1 || input_type_.right_ == 1)
    {
        frame_++;
    }
    else if (input_type_.attack_ != 1)
    {
        if (status_ == MOVE_RIGHT_) 
        {
            LoadImage ("img//stand_right.jpg", des, false);
            frame_++;
        }
        else if (status_ == MOVE_LEFT_)
        {
            LoadImage ("img//stand_right.jpg", des, true);
            flip = SDL_FLIP_HORIZONTAL;
            frame_++;
        }
    }

    if (frame_ >= 8)
    {
        frame_ = 0;
    }

    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopyEx (des, p_object_, current_clip, &renderQuad, 0, NULL, flip);
}

void PlayerObject::Show_Attack (SDL_Renderer* des, SDL_RendererFlip flip)
{
    if (input_type_.attack_ == 1)
    {
        if (input_type_.stand_right_ == 1) 
        {
            LoadImage_Attack ("img//attack_right.png", des, false);
            frame_++;
        }
        else if (input_type_.stand_left_ == 1)
        {
            LoadImage_Attack ("img//attack_right.png", des, true);
            flip = SDL_FLIP_HORIZONTAL;
            frame_++;
        }
        /*LoadImage_Attack ("img//attack_right.png", des, true);
        frame_++;*/
    }

    if (frame_ >= 8)
    {
        frame_ = 0;
    }

    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopyEx (des, p_object_, current_clip, &renderQuad, 0, NULL, flip);
}

void PlayerObject::HandleInputAction( SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_RIGHT:
            {
                status_ = MOVE_RIGHT_;
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                input_type_.stand_right_ = 1;
                input_type_.stand_left_ = 0;
            }
            break;
            case SDLK_LEFT:
            {
                status_ = MOVE_LEFT_;
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                input_type_.stand_left_ = 1;
                input_type_.stand_right_ = 0;
            }
            break;
            case SDLK_SPACE:
            {
                input_type_.jump_ = 1;
                input_type_.attack_ = 0;
                status_ = JUMP_UP_;
            }
            break;
            case SDLK_z:
            {
                input_type_.attack_ = 1;
                if (status_ != ATTACK_)
                {
                    status_ = ATTACK_;
                }
            }
            break;
            case SDLK_x:
            {
                input_type_.attack_ = 1;
                status_ = SPECIAL_ATTACK_;
                std::vector<SlashSkill*> p_skill_list_ = get_skill_list();
                SlashSkill* slash_skill = new SlashSkill();
                if (!slash_skill) {
                    std::cerr << "Failed to create SlashSkill object\n";
                }
                bool ret = slash_skill->LoadImage("img//Slash_skill.png", screen, false);
                if (ret)
                {
                    slash_skill->set_frame_width(slash_skill->get_frame_width());
                    slash_skill->set_frame_height(slash_skill->get_frame_height());
                    slash_skill->set_x_val(15);
                    slash_skill->set_y_val(0);
                    slash_skill->set_is_explosion(false);
                    slash_skill->set_x_pos(x_pos_ + 20);
                    slash_skill->set_y_pos(y_pos_);
                    slash_skill->set_frame_width(slash_skill->get_frame_width());
                    slash_skill->set_frame_height(slash_skill->get_frame_height());
                    slash_skill->Skill_Move(SCREEN_WIDTH, SCREEN_HEIGHT);
                    p_skill_list_.push_back(slash_skill);
                    for (int i = 0; i < p_skill_list_.size(); i++)
                    {
                        SlashSkill* p_skill = p_skill_list_.at(i);
                        if (p_skill)
                        {
                            if (p_skill->get_is_explosion() == false)
                            {
                                p_skill->set_clip();
                                p_skill->Show(screen);
                            }
                            else
                            {
                                p_skill_list_.erase(p_skill_list_.begin() + i);
                                if (p_skill != NULL)
                                {
                                    delete p_skill;
                                    p_skill = NULL;
                                }
                            }
                        }
                    }
                }
                else
                {
                    std::cerr << "Failed to load image img//Slash_skill.png\n";
                }
            }
            break;
            default:
            break;
        }
    }

    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_RIGHT:
            {
                input_type_.right_ = 0;
                //status_ = 0;
            }
            break;
            case SDLK_LEFT:
            {
                input_type_.left_ = 0;
                //status_ = 0;
            }
            break;
            case SDLK_SPACE:
            {
                input_type_.jump_ = 0;
            
            }
            break;
            case SDLK_z:
            {
                input_type_.attack_ = 0;
                if (status_ == ATTACK_)
                {
                    status_ = MOVE_RIGHT_;
                }
            }
            break;
            case SDLK_x:
            {
                input_type_.attack_ = 0;
                if (status_ == SPECIAL_ATTACK_)
                {
                    status_ = MOVE_RIGHT_;
                }


            }
            break;
            default:
            break;
        }
    }
}



void PlayerObject::action_player ( Map& map_data )
{
    x_val_ = 0;
    y_val_ += GRAVITY_SPEED;

    if (y_val_ >= MAX_FALL_SPEED)
    {
        y_val_ = MAX_FALL_SPEED;
    }

    if (input_type_.left_ == 1)
    {
        x_val_ -= PLAYER_SPEED;
    }
    else if (input_type_.right_ == 1)
    {
        x_val_ += PLAYER_SPEED;
    }

    if (input_type_.jump_ == 1)
    {
        if (on_ground == true)
        {
        y_val_ = - JUMP_SPEED;
        input_type_.jump_ = 0;
        on_ground = false;
        }

    }
    check_action_player (map_data);
    lock_map_to_character (map_data);
}

void PlayerObject::lock_map_to_character(Map& map_data) 
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
    if (map_data.start_x_ < 0)
    {
        map_data.start_x_ = 0;
    }
    else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ >= y_pos_ - (SCREEN_HEIGHT / 2);
    if (map_data.start_y_ < 0)
    {
        map_data.start_y_ = 0;
    }
    else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
    {
        map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
    }    

}


void PlayerObject::check_action_player (Map& map_data)
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
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }
        }
        else if (x_val_ < 0)
        {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
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
            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                on_ground = true;
            }
        }
        else if (y_val_ < 0)
        {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                y_pos_ = y1 * TILE_SIZE;
                y_pos_ += (height_frame_ + 2);
                y_val_ = 0;
                on_ground = false;
            }
        }
    }

    if (map_data.tile[y1][x2] == MONEY_COIN || map_data.tile[y2][x2] == MONEY_COIN ||
        map_data.tile[y2][x1] == MONEY_COIN || map_data.tile[y1][x2] == MONEY_COIN ||
        map_data.tile[y1][x2 + 1] == MONEY_COIN || map_data.tile[y2][x2 + 1] == MONEY_COIN ||
        map_data.tile[y1][x1 - 1] == MONEY_COIN || map_data.tile[y2][x1 - 1] == MONEY_COIN)
    {
        map_data.tile[y1][x2] = 0;
        //map_data.tile[y2][x2] = 0;
        map_data.tile[y1][x1] = 0;
        //map_data.tile[y2][x1] = 0;
        map_data.tile[y1][x2 + 1] = 0;
        map_data.tile[y1][x1 - 1] = 0;
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0) 
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }
}




