#pragma once
#include <windows.h>
#include "Utilities.h"
#include <array>

enum object_ID
{
    empty_id,

    cell_id,
};

struct cell
{
    int x0, y0, x1, y1;
    bool selected = false;
    int p_x, p_y;
};

union object_type
{
    struct cell cell;
};

struct object_types
{
    object_ID id;
    object_type object;
};

struct Render_State
{
    int height, width;
    void* memory;
    object_types* data;


    BITMAPINFO bitmap_info;
};

