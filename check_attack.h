#ifndef CHECK_ATTACK_H_
#define CHECK_ATTACK_H_
#include "common_function.h"
#include "base_object.h"
#include "player_object.h"
#include "threats.h"


bool CheckAttack(PlayerObject& player, std::vector<ThreatsObject*>& threats_list);
bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);


#endif