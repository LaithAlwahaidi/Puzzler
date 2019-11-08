#pragma once
#include "win32_platform.h"
#include "Utilities.h"
#include "array"

class Draw
{
private:
    // struct CHAR {
    //     int id;
    //     std::array<std::array<
    // }
    Render_State* r_s;
    void draw_rect_pixels(int x0, int y0, int x1, int y1, u32 color);
    // std::array<void *>
public:
    Draw(Render_State* rs);
    void draw_background(u32 color);
    void draw_rect(float x, float y, float half_x, float half_y, u32 color);
    void draw_box(float x, float y, float half_x, float half_y, int thickness, u32 color);
    void draw_cell(float x, float y, float half_x, float half_y, int thickness, u32 color, int p_x, int p_y, bool highlight);
    void highlight_cell(float x, float y, float half_x, float half_y, int thickness, u32 color);
    void draw_char(u8 c, float x, float y, int size, u32 color);
};