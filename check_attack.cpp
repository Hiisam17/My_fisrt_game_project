#include "common_function.h"
#include "base_object.h"
#include "player_object.h"
#include "threats.h"



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

void CheckAttack(PlayerObject& player, std::vector<ThreatsObject*>& threats_list)
{
    SDL_Rect player_rect = player.get_player_box(player_rect);
    for (int i = 0; i < threats_list.size(); i++)
    {
        SDL_Rect threats_rect = threats_list.at(i)->get_threats_box(threats_rect);
        if (CheckCollision(player_rect, threats_rect))
        {
            if (player.get_attack() == true)
            {
                threats_list.erase(threats_list.begin() + i);
            }
            else
            {
                player.get_injured();
                player.set_hp(player.get_hp() - 1);
                if (player.get_hp() <= 0)
                {
                    player.set_dead(true);
                }
            }
        }
    }
}

