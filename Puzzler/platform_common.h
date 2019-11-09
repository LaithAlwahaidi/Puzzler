#pragma once
//#include <array>

struct Button_State
{
    bool is_down;
    bool changed;
};

enum
{
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,

    BUTTON_COUNT, //last
};


enum Screen_State
{
    SUDOKU_SCREEN,

    SCREEN_COUNT,
};

struct Input
{
    Button_State buttons[BUTTON_COUNT];
    Screen_State screen;
    bool mouse_drag = false;
    bool is_higlighted[9][9];
};