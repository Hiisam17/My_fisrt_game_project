#ifndef CHECK_ATTACK_H_
#define CHECK_ATTACK_H_
#include "common_function.h"
#include "base_object.h"
#include "player_object.h"
#include "threats.h"
#include "explosion_.h"

bool CheckAttack(PlayerObject& player, std::vector<ThreatsObject*>& threats_list, ExplosionObject& exp_object);
bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);


#endif