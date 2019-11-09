#include "App.h"
#include <iostream>

SudokuApp::SudokuApp(Draw& draw)
    : draw(draw)
{
}

void SudokuApp::simulate(Input* input)
{
    draw.draw_background(0xffffff);

    if (input->screen == 0) {
        drawSudoku(input);
    }
    draw.draw_digit();
}

void SudokuApp::drawSudoku(Input* input)
{
    // inner cells
    for (int r = 4; r > -5; r--)
    {
        for (int c = -4; c < 5; c++)
        {
            draw.draw_cell((0.3 / 4.5) * c, (0.3 / 4.5) * r, 0.3 / 9, 0.3 / 9, 1, 0x737373, c + 4, -r + 4, input->is_higlighted[-r + 4][c + 4]);
        }
    }
    // 3x3 cells
    for (int r = 1; r > -2; r--)
    {
        for (int c = -1; c < 2; c++)
        {
            draw.draw_box((0.3 / 1.5) * c, (0.3 / 1.5) * r, 0.3 / 3, 0.3 / 3, 3, 0x4d4d4d);
        }
    }
    // outer cage
    draw.draw_box(0, 0, .305, .305, 7, 0x000000);
}