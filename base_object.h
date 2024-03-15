#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "common_function.h" // Định nghĩa các hàm chung

class base_object {
public:
    base_object(); // Constructor
    ~base_object(); // Destructor

    // Thiết lập vị trí cho đối tượng
    void set_rect(int &x, int &y) { rect_.x = x; rect_.y = y; }
    
    // Lấy hình chữ nhật mô tả vị trí của đối tượng
    SDL_Rect GetRect() const { return rect_; }
    
    // Lấy texture của đối tượng
    SDL_Texture* GetObject() { return p_object_; }

    // Tải hình ảnh từ đường dẫn path và render lên màn hình screen
    virtual bool LoadImage(std::string path, SDL_Renderer* screen);
    
    // Render đối tượng lên renderer des, với clip là phần cần cắt ra (nếu có)
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    
    // Giải phóng texture
    void Free();

protected:
    SDL_Texture* p_object_; // Texture của đối tượng
    SDL_Rect rect_; // Hình chữ nhật mô tả vị trí và kích thước của đối tượng
};

#endif