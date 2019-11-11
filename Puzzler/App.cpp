#include "App.h"
#include <iostream>
#include "Container.h"

SudokuApp::SudokuApp(Draw& draw, Render_State* rs)
    : draw(draw), rs(rs)
{
}

void SudokuApp::simulate(Input* input)
{
    draw.draw_background(0xffffff);

    Container c(.1f, .1f, 200, 200, rs, draw);
    c.DrawCell(0, 0, 50, 50, 1, 0x737373, 0, 0, input->is_higlighted[0][0]);
    Container c2 = c.CreateContainer(.5f, .5f, 50, 50);
    c2.DrawCell(0, 0, 30, 30, 1, 0x737373, 1, 1, input->is_higlighted[1][1]);

    if (input->screen == 0) {
        //drawSudoku(input);
    }
    draw.draw_digit('2', 0, 0);
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

            // size is half size
            draw.draw_cell(((float)2 / 9) * c, ((float)2 / 9) * r, size, size, size * 9, size * 9, 1, 0x737373, c + 4, -r + 4, input->is_higlighted[-r + 4][c + 4]);

            int digit = input->digit[-r + 4][c + 4];
            if (digit > 0)
                draw.draw_digit('0' + digit, ((float)2 / 9) * c, ((float)2 / 9) * r, size * 9, size * 9);
        }
    }
    // 3x3 cells
    for (int r = 1; r > -2; r--)
    {
        for (int c = -1; c < 2; c++)
        {
            //draw.draw_box((0.3 / 1.5) * c, (0.3 / 1.5) * r, (float)0.3 / 3, (float)0.3 / 3, 3, 0x4d4d4d);

            draw.draw_box(((float)2 / 3) * c, ((float)2 / 3) * r, size * 3, size * 3, size * 9, size * 9, 2, 0x4d4d4d);
        }
    }
    // outer cage
    //draw.draw_box(0, 0, (float).305, (float).305, 7, 0x000000);
    draw.draw_box(0, 0, size * 9, size * 9, size * 9, size * 9, 7, 0x000000);
}