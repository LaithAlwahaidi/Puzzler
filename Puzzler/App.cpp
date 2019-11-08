#include "App.h"
#include <iostream>

SudokuApp::SudokuApp(Draw& draw)
    : draw(draw)
{
}

float pos_x = 0.f;
float pos_y = 0.f;
void SudokuApp::simulate(Input* input)
{
    draw.draw_background(0xffffff);

    if (input->screen == 0) {

        for (int r = 4; r > -5; r--)
        {
            for (int c = -4; c < 5; c++)
            {
                draw.draw_cell((0.3 / 4.5) * c, (0.3 / 4.5) * r, 0.3 / 9, 0.3 / 9, 1, 0x737373, c + 4, -r + 4, input->is_higlighted[-r + 4][c + 4]);
            }
        }

        /*for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                draw.draw_cell((0.3 / 4.5) * i, (0.3 / 4.5) * j, 0.3 / 9, 0.3 / 9, 1, 0x737373);
                draw.draw_cell((0.3 / 4.5) * -i, (0.3 / 4.5) * j, 0.3 / 9, 0.3 / 9, 1, 0x737373);
                draw.draw_cell((0.3 / 4.5) * -i, (0.3 / 4.5) * -j, 0.3 / 9, 0.3 / 9, 1, 0x737373);
                draw.draw_cell((0.3 / 4.5) * i, (0.3 / 4.5) * -j, 0.3 / 9, 0.3 / 9, 1, 0x737373);
            }
        }*/
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                draw.draw_box((0.3 / 1.5) * i, (0.3 / 1.5) * j, 0.3 / 3, 0.3 / 3, 3, 0x4d4d4d);
                draw.draw_box((0.3 / 1.5) * -i, (0.3 / 1.5) * j, 0.3 / 3, 0.3 / 3, 3, 0x4d4d4d);
                draw.draw_box((0.3 / 1.5) * -i, (0.3 / 1.5) * -j, 0.3 / 3, 0.3 / 3, 3, 0x4d4d4d);
                draw.draw_box((0.3 / 1.5) * i, (0.3 / 1.5) * -j, 0.3 / 3, 0.3 / 3, 3, 0x4d4d4d);
            }
        }
    }
    /*if (input->screen == 0) {

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                draw.highlight_cell((0.3 / 4.5) * i, (0.3 / 4.5) * j, 0.3 / 9, 0.3 / 9, 1, 0x737373);
                draw.highlight_cell((0.3 / 4.5) * -i, (0.3 / 4.5) * j, 0.3 / 9, 0.3 / 9, 1, 0x737373);
                draw.highlight_cell((0.3 / 4.5) * -i, (0.3 / 4.5) * -j, 0.3 / 9, 0.3 / 9, 1, 0x737373);
                draw.highlight_cell((0.3 / 4.5) * i, (0.3 / 4.5) * -j, 0.3 / 9, 0.3 / 9, 1, 0x737373);
            }
        }
    }*/

    draw.draw_box(0, 0, .305, .305, 7, 0x000000);


    // renderer.draw_rect(pos_x, pos_y, .1, .1, 0x00ff22);
}