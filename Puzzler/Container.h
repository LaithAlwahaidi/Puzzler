#pragma once
#include "win32_platform.h"
#include "Draw.h"

class Container
{
private:
    int x, y;
    int width, height;
    Render_State* rs;
    Draw& d;

    Draw::square get_coords(float x, float y, int width, int height);
    Draw::square get_coords(float x, float y, float width, float height);

public:
    Container(float x, float y, float width, float height, Render_State* rs, Draw& d);
    Container(float x, float y, int width, int height, Render_State* rs, Draw& d);
    Container(int x, int y, int width, int height, Render_State* rs, Draw& d);
    Container* CreateContainer(float x, float y, float width, float height);
    Container* CreateContainer(float x, float y, int width, int height);

    void DrawCell(float x, float y, int width, int height, int thickness, u32 color, int p_x, int p_y, bool highlight);
    void DrawCell(float x, float y, float width, float height, int thickness, u32 color, int p_x, int p_y, bool highlight);

    void draw_box(float x, float y, int width, int height, int thickness, u32 color);
    void draw_box(float x, float y, float width, float height, int thickness, u32 color);

    void draw_rect(float x, float y, int width, int height, u32 color);
    void draw_rect(float x, float y, float width, float height, u32 color);

    void draw_char(char c, float x, float y);
};