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
    //draw.draw_digit();
}

void SudokuApp::drawSudoku(Input* input)
{
    // inner cells
    int size = 32;
    for (int r = 4; r > -5; r--)
    {
        for (int c = -4; c < 5; c++)
        {
            //draw.draw_cell((0.3 / 4.5) * c, (0.3 / 4.5) * r, (float)0.3 / 9, (float)0.3 / 9, 1, 0x737373, c + 4, -r + 4, input->is_higlighted[-r + 4][c + 4]);

            // 
            draw.draw_cell((((float)32 / 9) / (size / 2)) * c, (((float)32 / 9) / (size / 2)) * r, size, size, size * 9, size * 9, 1, 0x737373, c + 4, -r + 4, input->is_higlighted[-r + 4][c + 4]);
        }
    }
    // 3x3 cells
    for (int r = 1; r > -2; r--)
    {
        for (int c = -1; c < 2; c++)
        {
            //draw.draw_box((0.3 / 1.5) * c, (0.3 / 1.5) * r, (float)0.3 / 3, (float)0.3 / 3, 3, 0x4d4d4d);
            //draw.draw_box((0.3 / 1.5) * c, (0.3 / 1.5) * r, size * 3, size * 3, 3, 0x4d4d4d);

            draw.draw_box((((float)32 / 3) / (size / 2)) * c, (((float)32 / 3) / (size / 2)) * r, size * 3, size * 3, size * 9, size * 9, 2, 0x4d4d4d);
        }
    }
    // outer cage
    //draw.draw_box(0, 0, (float).305, (float).305, 7, 0x000000);
    draw.draw_box(0, 0, size * 9, size * 9, size * 9, size * 9, 7, 0x000000);
}