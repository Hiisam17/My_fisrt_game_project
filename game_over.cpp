#include "common_function.h"
#include "base_object.h"
#include "game_map.h"
#include "player_object.h"
#include "game_over.h"

bool PlayerObject::is_game_over(Map& map_data)
{
    bool ret = false;

    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min - 6) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    if (y2 >= MAX_MAP_Y && map_data.tile[y2][x1] == BLANK_TILE && map_data.tile[y2][x2] == BLANK_TILE)
    {
        ret = true;
    }
    else if (map_data.tile[y2][x1] == GOAL_POINT || 
             map_data.tile[y2][x2] == GOAL_POINT ||
             map_data.tile[y1][x1] == GOAL_POINT ||
             map_data.tile[y1][x2] == GOAL_POINT)
    {
        ret = true;
    }
    return ret;
}
