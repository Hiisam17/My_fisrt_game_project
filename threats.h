#ifndef THREATS_H_
#define THREATS_H_

#include "common_function.h"
#include "base_object.h"

class ThreatsObject : public base_object
{
    public:
    ThreatsObject();
    ~ThreatsObject();

    void set_x_val(const float& xVal) {x_val_ = xVal;}
    void set_y_val(const float& yVal) {y_val_ = yVal;}

    void set_x_pos(const float& xPos) {x_pos_ = xPos;}
    void set_y_pos(const float& yPos) {y_pos_ = yPos;}

    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}

    void set_clips();
    void SetMapXY (const int &map_x, const int &map_y) {map_x_ = map_x; map_y_ = map_y;}
    bool LoadImage (std::string path, SDL_Renderer* screen, bool flip = false);
    void Show(SDL_Renderer* des);

    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    void DoPlayer(Map& g_map);
    void CheckToMap(Map& g_map);

    SDL_Rect get_threats_box(SDL_Rect threats_box) {threats_box.x = x_pos_; threats_box.y = y_pos_; threats_box.w = width_frame_; threats_box.h = height_frame_; return threats_box;}

    private:

    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    int frame_;
    int comeback_time_;
    bool on_ground;

    int map_x_;
    int map_y_;

};

#endif