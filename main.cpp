#include "common_function.h"
#include "base_object.h"
#include "game_map.h"
#include "player_object.h"

base_object g_background;

bool InitData() 
{
    bool success = true;
    // Khởi tạo thư viện SDL2
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        return false;
    }
    // Thiết lập chất lượng scaling cho renderer
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Tạo cửa sổ SDL2 với các thông số được chỉ định
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
        // Tạo renderer để vẽ hình ảnh lên cửa sổ
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
        {
            success = false;
        }
        else 
        {
            // Thiết lập màu vẽ cho renderer
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            // Khởi tạo thư viện SDL_image để làm việc với hình ảnh
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                success = false;
            }
        }
    }

    return success;
}

bool LoadBackground()
{
    // Tải hình ảnh nền từ file và hiển thị lên màn hình
    bool ret = g_background.LoadImage("img//background.png", g_screen);
    if (ret == false) 
    {
        return false;
    }
    return true;
}

void close() 
{
    // Giải phóng bộ nhớ và đóng tất cả các tài nguyên đã khởi tạo bởi SDL và SDL_image
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    // Kiểm tra việc khởi tạo dữ liệu
    if (InitData() == false) {
        return -1;
    }

    // Tiến hành tải hình ảnh nền
    if (LoadBackground() == false) {
        return -1;
    }

    GameMap game_map;
    #pragma GCC diagnostic ignored "-Wwrite-strings"
    game_map.LoadMap("map\\map01.dat");
    #pragma GCC diagnostic warning "-Wwrite-strings"
    game_map.LoadTiles(g_screen);

    PlayerObject p_player;
    p_player.LoadImage ("img//player_right.png", g_screen);
    p_player.set_clips();

    bool is_quit = false;
    // Vòng lặp chính của chương trình
    while (!is_quit) {
        // Xử lý sự kiện SDL_QUIT (khi người dùng đóng cửa sổ)
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction (g_event, g_screen);
        }

        // Làm mới cửa sổ
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        // Hiển thị hình ảnh nền
        g_background.Render(g_screen, NULL);

        Map map_data = game_map.get_game_map();

        p_player.HandleBullet(g_screen);
        p_player.action_player(map_data);
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        if (p_player.is_game_over(map_data) == true)
        {
            break;
        }

        // Cập nhật màn hình
        SDL_RenderPresent(g_screen);

        SDL_Delay(30);
    }
    // Giải phóng tài nguyên và kết thúc chương trình
    close();
    return 0;
}
