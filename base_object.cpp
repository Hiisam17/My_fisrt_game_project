#include "base_object.h"

// Constructor
base_object::base_object()
{
    // Khởi tạo con trỏ p_object_ và các thành phần của rect_
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

// Destructor
base_object::~base_object()
{
    // Gọi hàm Free() để giải phóng bộ nhớ trước khi đối tượng bị hủy
    Free();
}

// Hàm tải hình ảnh từ đường dẫn path và render lên màn hình
bool base_object::LoadImage(std::string path, SDL_Renderer* screen)
{
    // Khai báo con trỏ mới cho texture và surface
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());

    // Kiểm tra load_surface
    if (load_surface != NULL) {
        // Thiết lập màu trong suốt cho một màu cụ thể trên surface
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface -> format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        
        // Tạo texture mới từ surface
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL) {
            // Cập nhật kích thước của rect_ theo kích thước của surface
            rect_.w = load_surface -> w;
            rect_.h = load_surface -> h;
        }

        // Giải phóng bộ nhớ cho surface
        SDL_FreeSurface(load_surface);
    }

    // Gán con trỏ p_object_ bằng texture mới
    p_object_ = new_texture;

    // Trả về true nếu tải hình ảnh thành công
    return p_object_ != NULL;
}

// Hàm render hình ảnh lên màn hình
void base_object::Render(SDL_Renderer* des, const SDL_Rect *clip /* NULL */)
{
    // Tạo một rect mới để render
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    // Render texture lên màn hình
    SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

// Hàm giải phóng texture và reset kích thước của rect_
void base_object::Free()
{
    if (p_object_ != NULL) {
        // Giải phóng texture
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        // Reset kích thước của rect_
        rect_.w = 0;
        rect_.h = 0;
    }
}