#include "common_function.h"
#include "base_object.h"
#include "game_map.h"
#include "player_object.h"
#include "threats.h"
#include "check_attack.h"
#include "text_object.h"
#include "menu.h"

base_object g_background;
TTF_Font* font_time = NULL;

bool InitData() 
{
    bool success = true;

    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");


    g_window = SDL_CreateWindow("CONTRA GAME - GAME_CODING_PRACTICE",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, 
                                 SCREEN_WIDTH, SCREEN_HEIGHT, 
                                 SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        success = false;
    }
    else
    {

        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
        {
            success = false;
        }
        else 
        {

            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                success = false;
            }
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("font//dlxfont_.ttf", 20);
        if (font_time == NULL)
        {
            success = false;
        }
        
    }

    return success;
}

bool LoadBackground()
{

    bool ret = g_background.LoadImage("img//background.png", g_screen, false);
    if (ret == false) 
    {
        return false;
    }
    return true;
}

void close() 
{

    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObject*> MakeThreatsList()
{
    std::vector<ThreatsObject*> list_threats; 

    ThreatsObject* dynamic_threats = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threats = (dynamic_threats + i);
        if (p_threats != NULL)
        {
            p_threats->LoadImage("img//threat_left.png", g_screen, true);
            p_threats->set_clips();
            p_threats->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREATS);
            p_threats->set_x_pos(700 + i * 1500);
            p_threats->set_y_pos(250);

            int pos1 = p_threats->get_x_pos() - 60;
            int pos2 = p_threats->get_x_pos() + 60;
            p_threats->set_animation_pos(pos1, pos2);

            list_threats.push_back(p_threats);
        }
    }

    ThreatsObject* threats_object = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threats = (threats_object + i);
        if (p_threats != NULL)
        {
            p_threats->LoadImage("img//threat_.png", g_screen, true);
            p_threats->set_clips();
            p_threats->set_x_pos(400 + i * 1200);
            p_threats->set_y_pos(250);
            p_threats->set_type_move(ThreatsObject::STATIC_THREATS);
            p_threats->set_input_left(0);

            list_threats.push_back(p_threats);
        }
    }
    return list_threats;
}


int main(int argc, char* argv[])
{

    if (InitData() == false) {
        return -1;
    }


    if (LoadBackground() == false) {
        return -1;
    }

    GameMap game_map;
    #pragma GCC diagnostic ignored "-Wwrite-strings"
    game_map.LoadMap("map\\map01.dat");
    #pragma GCC diagnostic warning "-Wwrite-strings"
    game_map.LoadTiles(g_screen);

    PlayerObject p_player;
    p_player.LoadImage("img//stand_right.jpg", g_screen, false);
    //p_player.set_clips();

    std::vector<ThreatsObject*> threats_list = MakeThreatsList();

    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);

    bool is_quit = false;

    is_quit = showMenu(g_screen);

    while (!is_quit) {

        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction (g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map map_data = game_map.get_game_map();

        p_player.action_player(map_data);
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);

        int player_status = p_player.get_status();
        if (player_status == PlayerObject::ATTACK_ || player_status == PlayerObject::SPECIAL_ATTACK_)
        {
            p_player.Show_Attack(g_screen);
            p_player.set_clips();
        }
        else if (player_status != PlayerObject::ATTACK_  || player_status != PlayerObject::SPECIAL_ATTACK_)
        {

            p_player.Show(g_screen);
            p_player.set_clips();
        }
        
        p_player.HandleSkill(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        bool life_check = false;

        for (int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObject* p_threats = threats_list.at(i);
            if (p_threats != NULL)
            {
                p_threats->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threats->ImpMoveType(g_screen);
                p_threats->DoPlayer(map_data);
                p_threats->Show(g_screen);
               life_check = CheckAttack(p_player, threats_list);
            }
        }

        Check_Special_Attack(p_player, threats_list);

        if (life_check == true)
        {
            is_quit = true;
            break;
        }

        bool is_game_over = p_player.is_game_over(map_data, p_player);
        if (is_game_over == true)
        {
            is_quit = true;
            break;
        }

        std::string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 300 - time_val;
        if (val_time <= 0)
        {
            is_quit = true;
            break;
        }
        else
        {
            std::string str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
        }

        std::string str_mark = "Mark: ";
        int val_mark = p_player.get_mark();
        if (val_mark < 0)
        {
            val_mark = 0;
        }
        else
        {
            str_mark += std::to_string(val_mark);

            mark_game.SetText(str_mark);
            mark_game.LoadFromRenderText(font_time, g_screen);
            mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5, 15);

        }

        SDL_RenderPresent(g_screen);

        SDL_Delay(30);
    }

    close();
    return 0;
}


