#include "Container.h"

Container::Container(float x, float y, float width, float height, Render_State* rs, Draw& d)
    : x(x* rs->width), y(y* rs->height),
    width(width* rs->width), height(height* rs->height),
    rs(rs), d(d)
{
}

Container::Container(float x, float y, int width, int height, Render_State* rs, Draw& d)
    : x(x* rs->width), y(y* rs->height),
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

Container* Container::CreateContainer(float x, float y, float width, float height)
{
    int x0 = x * this->width;
    int y0 = y * this->height;
    int widthn = width * this->width;
    int heightn = height * this->height;
    if ((x0 + widthn > this->x + this->width) || (y0 + heightn > this->y + this->height))
        return NULL;

    return new Container(x0 + this->x, y0 + this->y, widthn, heightn, rs, d);
}

Container* Container::CreateContainer(float x, float y, int width, int height)
{
    int x0 = x * this->width;
    int y0 = y * this->height;
    if ((x0 + width > this->width) || (y0 + height > this->height))
        return NULL;

    return new Container(x0 + this->x, y0 + this->y, width, height, rs, d);
}

void Container::DrawCell(float x, float y, int width, int height, int thickness, u32 color, int p_x, int p_y, bool highlight)
{
    Draw::square points = get_coords(x, y, width, height);

    d.draw_cell(points, thickness, color, p_x, p_y, highlight);
}

void Container::DrawCell(float x, float y, float width, float height, int thickness, u32 color, int p_x, int p_y, bool highlight)
{
    Draw::square points = get_coords(x, y, width, height);
    d.draw_cell(points, thickness, color, p_x, p_y, highlight);
}

void Container::draw_box(float x, float y, float width, float height, int thickness, u32 color)
{
    Draw::square points = get_coords(x, y, width, height);
    d.draw_box(points, thickness, color);
}

void Container::draw_box(float x, float y, int width, int height, int thickness, u32 color)
{
    Draw::square points = get_coords(x, y, width, height);
    d.draw_box(points, thickness, color);
}

void Container::draw_rect(float x, float y, float width, float height, u32 color)
{
    Draw::square points = get_coords(x, y, width, height);
    d.draw_rect_pixels(points, color);
}

void Container::draw_rect(float x, float y, int width, int height, u32 color)
{
    Draw::square points = get_coords(x, y, width, height);
    d.draw_rect_pixels(points, color);
}

Draw::square Container::get_coords(float x, float y, int width, int height)
{
    Draw::square points = {
        x * this->width + this->x,
        y * this->height + this->y,
        x * this->width + this->x + width,
        y * this->height + this->y + height
    };

    return points;
}

Draw::square Container::get_coords(float x, float y, float width, float height)
{
    int widthp = width * this->width;
    int heightp = height * this->height;
    return get_coords(x, y, widthp, heightp);
}

void Container::draw_char(char c, float x, float y)
{
    Draw::square points = get_coords(x, y, 0, 0);
    d.draw_digit(c, points.x0, points.y0);
}