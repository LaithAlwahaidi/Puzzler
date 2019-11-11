#include "Container.h"

Container::Container(float x, float y, float width, float height, Render_State* rs, Draw& d)
    : x(x* rs->width), y(y* rs->height),
    width(width* rs->width), height(height* rs->height + rs->height),
    rs(rs), d(d)
{
}

Container::Container(float x, float y, int width, int height, Render_State* rs, Draw& d)
    : x(x* rs->height), y(y* rs->height),
    width(width), height(height),
    rs(rs), d(d)
{
}

Container::Container(int x, int y, int width, int height, Render_State* rs, Draw& d)
    : x(x), y(y),
    width(width), height(height),
    rs(rs), d(d)
{
}

Container Container::CreateContainer(float x, float y, float width, float height)
{
    return Container(x + this->x, y + this->y, width * this->width, height * this->height, rs, d);
}

Container Container::CreateContainer(float x, float y, int width, int height)
{
    return Container((int)(x * this->width), (int)(y * this->height), width, height, rs, d);
}

void Container::DrawCell(float x, float y, int width, int height, int thickness, u32 color, int p_x, int p_y, bool highlight)
{
    Draw::square points = {
        x * this->width + this->x,
        y * this->height + this->y,
        x * this->width + width + this->x,
        y * this->height + height + this->y
    };

    d.draw_cell(points, thickness, color, p_x, p_y, highlight);
}