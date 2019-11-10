#pragma once
#include "win32_platform.h"
#include "Utilities.h"
#include "array"

class Draw
{
private:
    struct square
    {
        int x0, y0, x1, y1;
    };

    Render_State* r_s;
    void draw_rect_pixels(square points, u32 color);
    square raw_square_pixels(float x, float y, float half_x, float half_y);
    square raw_square_pixels(float x, float y, float half_x, float half_y, int scale_width, int scale_height);
    square raw_square_pixels(float x, float y, int width, int height, int scale_width, int scale_height);

public:
    Draw(Render_State* rs);
    void draw_background(u32 color);
    void draw_rect(float x, float y, float half_x, float half_y, u32 color);
    void draw_rect(float x, float y, int width, int height, int total_width, int total_height, u32 color);
    void draw_box(float x, float y, float half_x, float half_y, int thickness, u32 color);
    void draw_box(float x, float y, int width, int height, int total_width, int total_height, int thickness, u32 color);
    void draw_box(square points, int thickness, u32 color);
    void draw_cell(float x, float y, float half_x, float half_y, int thickness, u32 color, int p_x, int p_y, bool highlight);
    void draw_cell(float x, float y, int width, int height, int total_width, int total_height, int thickness, u32 color, int p_x, int p_y, bool highlight);
    void draw_cell(square points, int thickness, u32 color, int p_x, int p_y, bool highlight);
    void draw_sprite_pixels(int x, int y, int width, int height, u32* source);
    void draw_sprite(float x, float y, float half_x, float half_y, int width, int height, u32* source);
    void draw_digit();


};