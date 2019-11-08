#pragma once

#include "Draw.h"
#include "platform_common.h"

#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

class SudokuApp
{
private:
    Draw& draw;

public:
    SudokuApp(Draw& draw);
    void simulate(Input* input);
};