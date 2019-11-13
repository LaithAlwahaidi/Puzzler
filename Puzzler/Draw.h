#pragma once
#include "win32_platform.h"
#include "Utilities.h"
#include "vector"
#include <windows.h>
#pragma comment(lib, "WindowsCodecs.lib")
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")



class Draw
{
public:
    struct square
    {
        int x0, y0, x1, y1;
    };
private:

    struct mychar
    {
        char char_id;
        int font_size;
        int width, height;
        int xoffset, yoffset;
        int xadvance;
        u32* pixels;
    };

    Render_State* r_s;

    std::vector<mychar> my_chars;


public:
    Draw(Render_State* rs);
    void draw_background(u32 color);
    void draw_rect_pixels(square points, u32 color);
    void draw_box(square points, int thickness, u32 color);
    void draw_cell(square points, int thickness, u32 color, int p_x, int p_y, bool highlight);
    void draw_sprite_pixels(int x, int y, int width, int height, u32* source);
    void draw_sprite(float x, float y, float half_x, float half_y, int width, int height, u32* source);
    void draw_digit(char c, int x, int y);
    void draw_digit(char c, float x, float y, int scale_width, int scale_height);

};