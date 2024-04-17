#include "common_function.h"
#include "base_object.h"
#include "player_object.h"
#include "threats.h"
#include "check_attack.h"
#include "Slash_skill.h"


bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w - 30;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w - 10;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    if (left_a > right_b || right_a < left_b || top_a > bottom_b || bottom_a < top_b)
    {
        return false;
    }

    return true;
}

bool CheckCollision_Attack(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x -32;
    int right_a = object1.x + object1.w;
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

bool CheckAttack(PlayerObject& player, std::vector<ThreatsObject*>& threats_list, Mix_Chunk* g_sound_hit)
{
    SDL_Rect player_rect;
    player_rect.x = player.GetRect().x;
    player_rect.y = player.GetRect().y;
    player_rect.w = player.get_width_frame();
    player_rect.h = player.get_height_frame();

    bool check_injured = false;
    for (int i = 0; i < threats_list.size(); i++)
    {
        ThreatsObject* p_threats = threats_list.at(i);
        SDL_Rect threats_rect;
        threats_rect.x = p_threats->GetRect().x;
        threats_rect.y = p_threats->GetRect().y;
        threats_rect.w = p_threats->get_width_frame();
        threats_rect.h = p_threats->get_height_frame();

        if (CheckCollision(player_rect, threats_rect))
        {
            if (player.get_attack() == false)
            {
                check_injured = true;
            }
        }

        if (CheckCollision_Attack(player_rect, threats_rect))
        {
            if (player.get_attack() == true)
            {
                player.set_mark(1);
                threats_list.erase(threats_list.begin() + i);
                check_injured = false;
                Mix_PlayChannel(-1, g_sound_hit, 0);
            }
        }
    }

    return check_injured;
}

bool CheckCollision_Special_Attack(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
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

bool Check_Special_Attack(PlayerObject& player, std::vector<ThreatsObject*>& threats_list)
{
    bool ret = false;

    std::vector<slash_skill_object*> skill_list = player.get_skill_list();

    for (int t = 0; t < skill_list.size(); ++t)
    {
        slash_skill_object* p_skill = skill_list.at(t);
        SDL_Rect skill_rect;
        skill_rect.x = p_skill->GetRect().x;
        skill_rect.y = p_skill->GetRect().y;
        skill_rect.w = p_skill->get_width_frame();
        skill_rect.h = p_skill->get_height_frame();
        
        for (int k = 0; k < threats_list.size(); ++k)
        {
            ThreatsObject* p_threats = threats_list.at(k);
            SDL_Rect threats_rect;
            threats_rect.x = p_threats->GetRect().x;
            threats_rect.y = p_threats->GetRect().y;
            threats_rect.w = p_threats->get_width_frame();
            threats_rect.h = p_threats->get_height_frame();
            
            if (CheckCollision_Special_Attack(skill_rect, threats_rect))
            {
                std::cout << "va cham" << std::endl;
                player.set_mark(1);
                threats_list.erase(threats_list.begin() + k);
                player.RemoveSkill(t, skill_list);
                ret = true;
            }
            else
            {
                ret = false;
            }
        }
    }

    return ret;

}



