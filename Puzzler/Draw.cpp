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

using namespace std;

Draw::Draw(Render_State* rs)
    : r_s(rs)
{
    // CComPtr<IWICBitmapDecoder> decoder;
    // HR(decoder.CoCreateInstance(CLSID_WICPngDecoder));

    // CComPtr<IStream> stream;

    // // Create stream object here
    // ...

    //     HR(decoder->Initialize(
    //         stream,
    //         WICDecodeMetadataCacheOnDemand));
    // CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

    //IWICBitmapDecoder* pDecoder = NULL;
    //IWICImagingFactory* i_f = NULL;
    //LPCLSID* CLSID = NULL;

    //CoCreateInstance(
    //    CLSID_WICImagingFactory,
    //    NULL,
    //    CLSCTX_INPROC_SERVER,
    //    __uuidof(i_f),
    //    reinterpret_cast<void**>(&i_f));

    //i_f->CreateDecoderFromFilename(
    //    L"./assets/digits_0.png",
    //    NULL,
    //    GENERIC_READ,
    //    WICDecodeMetadataCacheOnDemand,
    //    &pDecoder);

    //IWICBitmapFrameDecode* pFrame = NULL;
    //pDecoder->GetFrame(0, &pFrame);

    int char_count;
    ifstream digit_info;
    digit_info.open("./assets/digits.fnt", ios::in);
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
                cout << char_count << '\n';
            }
            if (line_n > 3)
            {
                cout << "id=" << line.substr(8, line.find(" ", 8) - 8) << "s \n";
                cout << "x=" << line.substr(15, line.find(" ", 15) - 15) << "s \n";
            }
            line_n++;
        }
    }

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

void Draw::draw_rect_pixels(int x0, int y0, int x1, int y1, u32 color)
{
    x0 = Utils::clamp(0, x0, r_s->width);
    x1 = Utils::clamp(0, x1, r_s->width);
    y0 = Utils::clamp(0, y0, r_s->height);
    y1 = Utils::clamp(0, y1, r_s->height);

    for (int y = y0; y < y1; y++)
    {
        u32* pixel = (u32*)r_s->memory + x0 + y * r_s->width;
        for (int x = x0; x < x1; x++)
        {
            *pixel++ = color;
        }
    }
}

void Draw::draw_rect(float x, float y, float half_x, float half_y, u32 color)
{
    x *= r_s->height;
    y *= r_s->height;
    half_x *= r_s->height;
    half_y *= r_s->height;

    x += r_s->width / 2.f;
    y += r_s->height / 2.f;

    int x0 = x - half_x;
    int x1 = x + half_x;
    int y0 = y - half_y;
    int y1 = y + half_y;

    draw_rect_pixels(x0, y0, x1, y1, color);
}

void Draw::draw_box(float x, float y, float half_x, float half_y, int thickness, u32 color)
{
    x *= r_s->height;
    y *= r_s->height;
    half_x *= r_s->height;
    half_y *= r_s->height;

    x += r_s->width / 2.f;
    y += r_s->height / 2.f;

    int x0 = x - half_x;
    int x1 = x + half_x;
    int y0 = y - half_y;
    int y1 = y + half_y;

    draw_rect_pixels(x0, y1 - thickness, x1, y1, color); // top
    draw_rect_pixels(x1 - thickness, y0, x1, y1, color); // right
    draw_rect_pixels(x0, y0, x1, thickness + y0, color); // bottom
    draw_rect_pixels(x0, y0, thickness + x0, y1, color); // left

}

void Draw::draw_cell(float x, float y, float half_x, float half_y, int thickness, u32 color, int p_x, int p_y, bool highlight)
{
    x *= r_s->height;
    y *= r_s->height;
    half_x *= r_s->height;
    half_y *= r_s->height;

    x += r_s->width / 2.f;
    y += r_s->height / 2.f;

    int x0 = x - half_x;
    int x1 = x + half_x;
    int y0 = y - half_y;
    int y1 = y + half_y;


    draw_rect_pixels(x0, y1 - thickness, x1, y1, color); // top
    draw_rect_pixels(x1 - thickness, y0, x1, y1, color); // right
    draw_rect_pixels(x0, y0, x1, thickness + y0, color); // bottom
    draw_rect_pixels(x0, y0, thickness + x0, y1, color); // left


    x0 = Utils::clamp(0, x0, r_s->width);
    x1 = Utils::clamp(0, x1, r_s->width);
    y0 = Utils::clamp(0, y0, r_s->height);
    y1 = Utils::clamp(0, y1, r_s->height);

    if (highlight)
        draw_rect_pixels(x0 + thickness, y0 + thickness, x1 - thickness, y1 - thickness, 0xfffa61);

    cell cell_p = {};
    cell_p.x0 = x0;
    cell_p.x1 = x1;
    cell_p.y0 = y0;
    cell_p.y1 = y1;
    cell_p.p_x = p_x;
    cell_p.p_y = -p_y + 8;

    object_types o = {};
    o.id = cell_id;
    o.object.cell = (struct cell) cell_p;

    for (int y = y1; y > y0; y--)
    {
        object_types* pixel_object = (object_types*)(r_s->data) + x0 + y * r_s->width;
        //pixel_object[pixel_object->id];

        for (int x = x0; x < x1; x++)
        {
            //*pixel++ = color;
            *pixel_object = o;
            pixel_object++;
        }
    }
}

void Draw::highlight_cell(float x, float y, float half_x, float half_y, int thickness, u32 color)
{
    x *= r_s->height;
    y *= r_s->height;
    half_x *= r_s->height;
    half_y *= r_s->height;

    x += r_s->width / 2.f;
    y += r_s->height / 2.f;

    int x0 = x - half_x + thickness;
    int x1 = x + half_x - thickness;
    int y0 = y - half_y + thickness;
    int y1 = y + half_y - thickness;

    for (int y = y0; y < y1; y++)
    {
        object_types* pixel_object = (object_types*)(r_s->data) + x0 + y * r_s->width;
        for (int x = x0; x < x1; x++)
        {
            cell c = pixel_object->object.cell;
            if (c.selected)
            {
                draw_rect_pixels(x0, y0, x1, y1, 0xfffa61);
                return;
            }
            pixel_object++;
        }
    }



}


void Draw::draw_char(u8 c, float x, float y, int size, u32 color)
{
}