#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "common_function.h"

class base_object {
    public:
    base_object();
    ~base_object();
    void set_rect(int &x, int &y) {rect_.x = x; rect_.y = y;}
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture* GetObject() {return p_object_;}

    bool LoadImage(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();

    protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
};

#endif