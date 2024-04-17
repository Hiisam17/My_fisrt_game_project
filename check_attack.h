#ifndef CHECK_ATTACK_H_
#define CHECK_ATTACK_H_
#include "common_function.h"
#include "base_object.h"
#include "player_object.h"
#include "threats.h"


bool CheckAttack(PlayerObject& player, std::vector<ThreatsObject*>& threats_list, Mix_Chunk* g_sound_hit);
bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
bool CheckCollision_Special_Attack(const SDL_Rect& object1, const SDL_Rect& object2);
bool Check_Special_Attack(PlayerObject& player, std::vector<ThreatsObject*>& threats_list);
bool CheckCollision_Attack(const SDL_Rect& object1, const SDL_Rect& object2);

#endif