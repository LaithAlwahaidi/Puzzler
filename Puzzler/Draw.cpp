#include "Draw.h"
#include "win32_platform.h"
#include <fstream>
#include <iostream>
#include <string>
#include <wincodec.h>
#include <windows.h>
#pragma comment(lib, "WindowsCodecs.lib")
// #include <atlbase.h>
#include <Objbase.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace std;

Draw::Draw(Render_State* rs)
    : r_s(rs)
{
}

void Draw::draw_digit()
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    //Gdiplus::Bitmap b(L"assets/font_0.png");
    Gdiplus::Bitmap* b = Gdiplus::Bitmap::FromFile(L"assets/font1_0.png");
    //u32 i1 = b->GetFrameDimensionsCount();
    //u32 i2 = b->GetHeight();
    //u32 i3 = b->GetWidth();
    //Gdiplus::PixelFormat pf = b->GetPixelFormat();



    int char_count;
    ifstream digit_info;
    digit_info.open("assets/font1.fnt", ios::in);
    if (digit_info.is_open())
    {
        string line;
        int line_n = 0;
        while (getline(digit_info, line))
        {
            // int delim_e = line.find("=");
            // int delim_s = line.find(" ");

            if (line_n == 3)
            {
                char_count = stoi(line.substr(12, (line.length() - 12)));
            }
            if (line_n > 3 && char_count > 0)
            {
                char_count--;
                int i = line.find("id=", 0) + 3;
                int id = stoi(line.substr(i, line.find(" ", i)));
                i = line.find("x=", i) + 2;
                int x = stoi(line.substr(i, line.find(" ", i)));
                i = line.find("y=", i) + 2;
                int y = stoi(line.substr(i, line.find(" ", i)));
                i = line.find("width=", i) + 6;
                int width = stoi(line.substr(i, line.find(" ", i)));
                i = line.find("height=", i) + 7;
                int height = stoi(line.substr(i, line.find(" ", i)));
                i = line.find("xoffset=", i) + 8;
                int xoffset = stoi(line.substr(i, line.find(" ", i)));
                i = line.find("yoffset=", i) + 8;
                int yoffset = stoi(line.substr(i, line.find(" ", i)));
                i = line.find("xadvance=", i) + 9;
                int xadvance = stoi(line.substr(i, line.find(" ", i)));
                if (id == 120)
                {
                    u32* dest;
                    dest = new u32[width * height];
                    int ind = 0;
                    for (int r = height + y - 1; r >= y; r--)
                    {
                        for (int c = x; c < width + x; c++)
                        {
                            Gdiplus::Color col;

                            b->GetPixel(c, r, &col);
                            u32 dest_col =
                                col.GetR() << 16 |
                                col.GetG() << 8 |
                                col.GetB();
                            dest[ind] = dest_col;
                            ind++;
                        }
                    }
                    draw_sprite_pixels(300, 100, width, height, dest);
                    draw_sprite(0, 0, .01, .02, width, height, dest);
                    delete[] dest;
                    int k = 0;
                }

            }
            line_n++;
        }
    }
    delete[] b;
    Gdiplus::GdiplusShutdown(gdiplusToken);

    digit_info.close();
}

void Draw::draw_background(u32 color)
{
    u32* pixel = (u32*)r_s->memory;
    for (int y = 0; y < r_s->height; y++)
    {
        for (int x = 0; x < r_s->width; x++)
        {
            *pixel++ = color;
        }
    }
}

void Draw::draw_sprite_pixels(int x, int y, int width, int height, u32* source)
{
    //x = Utils::clamp(0, x, r_s->width);
    //y = Utils::clamp(0, y, r_s->height);

    u32 s_color;
    for (int y_d = 0; y_d < height; y_d++)
    {
        u32* dest = (u32*)r_s->memory + x + y * r_s->width + y_d * r_s->width;

        for (int x_d = 0; x_d < width; x_d++)
        {
            s_color = *(source + x_d + y_d * width);
            if (s_color > 0)
                *dest = s_color ^ 0xffffff;
            //*dest = 0x000000;
            dest++;
        }
    }
}

void Draw::draw_sprite(float x, float y, float half_x, float half_y, int width, int height, u32* source)
{
    x *= r_s->height;
    y *= r_s->height;
    half_x *= r_s->height;
    half_y *= r_s->height;

    x += r_s->width / 2.f;
    y += r_s->height / 2.f;

    float width_scale = (half_x * 2 / r_s->width) / ((float)width / (float)r_s->width);
    float height_scale = (half_y * 2 / r_s->height) / ((float)height / (float)r_s->height);

    int new_width = width * width_scale;
    int new_height = height * height_scale;

    u32* scaled_source = new u32[new_width * new_height];

    u32 s_color;
    for (int y_d = 0; y_d < new_height; y_d++)
    {
        for (int x_d = 0; x_d < new_width; x_d++)
        {
            s_color = source[((int)(round)(y_d / height_scale) * width) + ((int)(round)(x_d / width_scale))];
            scaled_source[y_d * new_width + x_d] = s_color;
        }
    }
    draw_sprite_pixels(x, y, new_width, new_height, scaled_source);

}


void Draw::draw_rect_pixels(square points, u32 color)
{
    points.x0 = Utils::clamp(0, points.x0, r_s->width);
    points.x1 = Utils::clamp(0, points.x1, r_s->width);
    points.y0 = Utils::clamp(0, points.y0, r_s->height);
    points.y1 = Utils::clamp(0, points.y1, r_s->height);

    for (int y = points.y0; y < points.y1; y++)
    {
        u32* pixel = (u32*)r_s->memory + points.x0 + y * r_s->width;
        for (int x = points.x0; x < points.x1; x++)
        {
            *pixel++ = color;
        }
    }
}

Draw::square Draw::raw_square_pixels(float x, float y, int width, int height, int scale_width, int scale_height)
{
    x *= scale_width;
    y *= scale_height;

    x += r_s->width / 2.f;
    y += r_s->height / 2.f;

    int x0 = x - width;
    int x1 = x + width;
    int y0 = y - height;
    int y1 = y + height;
    return square{ x0, y0, x1, y1 };
}

Draw::square Draw::raw_square_pixels(float x, float y, float half_x, float half_y, int scale_width, int scale_height)
{
    x *= scale_width;
    y *= scale_height;
    half_x *= scale_width;
    half_y *= scale_height;

    x += r_s->width / 2.f;
    y += r_s->height / 2.f;

    int x0 = x - half_x;
    int x1 = x + half_x;
    int y0 = y - half_y;
    int y1 = y + half_y;
    return square{ x0, y0, x1, y1 };
}

Draw::square Draw::raw_square_pixels(float x, float y, float half_x, float half_y)
{
    return raw_square_pixels(x, y, half_x, half_y, r_s->height, r_s->height);
}

void Draw::draw_rect(float x, float y, float half_x, float half_y, u32 color)
{
    draw_rect_pixels(raw_square_pixels(x, y, half_x, half_y), color);
}

void Draw::draw_rect(float x, float y, int width, int height, int total_width, int total_height, u32 color)
{
    square s = raw_square_pixels(x, y, width, height, total_width, total_height);
    draw_rect_pixels(s, color);
}


void Draw::draw_box(square points, int thickness, u32 color)
{
    square cur_box = {};

    cur_box.x0 = points.x0;
    cur_box.y0 = points.y1 - thickness;
    cur_box.x1 = points.x1;
    cur_box.y1 = points.y1;
    draw_rect_pixels(cur_box, color); // top

    cur_box.x0 = points.x1 - thickness;
    cur_box.y0 = points.y0;
    cur_box.x1 = points.x1;
    cur_box.y1 = points.y1;
    draw_rect_pixels(cur_box, color); // right

    cur_box.x0 = points.x0;
    cur_box.y0 = points.y0;
    cur_box.x1 = points.x1;
    cur_box.y1 = points.y0 + thickness;
    draw_rect_pixels(cur_box, color); // bottom

    cur_box.x0 = points.x0;
    cur_box.y0 = points.y0;
    cur_box.x1 = points.x0 + thickness;
    cur_box.y1 = points.y1;
    draw_rect_pixels(cur_box, color); // left
}

void Draw::draw_box(float x, float y, float half_x, float half_y, int thickness, u32 color)
{
    square points = raw_square_pixels(x, y, half_x, half_y);
    draw_box(points, thickness, color);
}

void Draw::draw_box(float x, float y, int width, int height, int total_width, int total_height, int thickness, u32 color)
{
    square s = raw_square_pixels(x, y, width, height, total_width, total_height);
    draw_box(s, thickness, color);
}


void Draw::draw_cell(square points, int thickness, u32 color, int p_x, int p_y, bool highlight)
{
    points.x0 += thickness;
    points.y0 += thickness;
    points.x1 -= thickness;
    points.y1 -= thickness;

    if (highlight)
        draw_rect_pixels(points, 0xfffa61);

    cell cell_p = {};
    cell_p.x0 = points.x0;
    cell_p.x1 = points.x1;
    cell_p.y0 = points.y0;
    cell_p.y1 = points.y1;
    cell_p.p_x = p_x;
    cell_p.p_y = -p_y + 8;

    object_types o = {};
    o.id = cell_id;
    o.object.cell = (struct cell) cell_p;

    for (int y = points.y1; y > points.y0; y--)
    {
        object_types* pixel_object = (object_types*)(r_s->data) + points.x0 + y * r_s->width;

        for (int x = points.x0; x < points.x1; x++)
        {
            *pixel_object = o;
            pixel_object++;
        }
    }
}

void Draw::draw_cell(float x, float y, int width, int height, int total_width, int total_height, int thickness, u32 color, int p_x, int p_y, bool highlight)
{

    square points = raw_square_pixels(x, y, width, height, total_width, total_height);
    draw_box(points, thickness, color);

    draw_cell(points, thickness, color, p_x, p_y, highlight);

}

void Draw::draw_cell(float x, float y, float half_x, float half_y, int thickness, u32 color, int p_x, int p_y, bool highlight)
{

    draw_box(x, y, half_x, half_y, thickness, color);

    square points = raw_square_pixels(x, y, half_x, half_y);
    draw_cell(points, thickness, color, p_x, p_y, highlight);
}