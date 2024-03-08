#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "common_function.h"
#include "base_object.h"

#define MAX_TILES 20

class TileMap : public base_object // Kế thừa từ class base object
{
    public:
        TileMap() {;}
        ~TileMap() {;}
};

class GameMap
{
    public:
        GameMap() {;}
        ~GameMap() {;}

        void LoadMap(char* name);
        void LoadTiles(SDL_Renderer* screen);
        void DrawMap(SDL_Renderer* screen);
    private:
        Map game_map_;
        TileMap tile_map[MAX_TILES];
};

#endif