#include "common_function.h"
#include "base_object.h"
#include "player_object.h"
#include "threats.h"
#include "check_attack.h"
#include "explosion_.h"



bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x + 15;
    int right_a = object1.x + object1.w - 15;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    if (left_a > right_b || right_a < left_b || top_a > bottom_b || bottom_a < top_b)
    {
        return false;
    }
    return true;
}

bool CheckAttack(PlayerObject& player, std::vector<ThreatsObject*>& threats_list, ExplosionObject& exp_object)
{
    SDL_Rect player_rect = player.get_player_box(player_rect);
    bool check_injured = false;
    for (int i = 0; i < threats_list.size(); i++)
    {
        SDL_Rect threats_rect = threats_list.at(i)->get_threats_box(threats_rect);
        if (CheckCollision(player_rect, threats_rect))
        {
            if (player.get_attack() == true)
            {
                check_injured = false;
                bool tRet = exp_object.LoadImage("img//BOOM_.png", g_screen, false);
                threats_list.erase(threats_list.begin() + i);
                if (!tRet) 
                {
                std::cerr << "Failed to load image img//boom_.png\n";
                }

                if (tRet)
                {
                    std::cout << "Explosion loaded\n";
                    //exp_object.set_frame(0);
                    exp_object.set_is_explosion(true);
                    exp_object.set_frame_width(threats_rect.w);
                    exp_object.set_frame_height(threats_rect.h);
                    exp_object.set_x_pos(threats_rect.x);
                    exp_object.set_y_pos(threats_rect.y);
                    exp_object.Show(g_screen);
                    exp_object.set_clip();
                }
            }
            else
            {
                check_injured = true;
            }
        }
    }

    return check_injured;
}

