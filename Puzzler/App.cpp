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

    if (input->screen == 0) {
        drawSudoku(input);
    }
}

void SudokuApp::drawSudoku(Input* input)
{
    int cell_size = 64;
    Container sudokubox((0.5f - (float)(cell_size * 9 / 2) / rs->width), (0.5f - (float)(cell_size * 9 / 2) / rs->height), cell_size * 9, cell_size * 9, rs, draw);

    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            Container* cellbox = sudokubox.CreateContainer((1.0 / 9) * r, (1.0 / 9) * c, cell_size, cell_size);
            if (!cellbox)
                return;
            cellbox->DrawCell(0.0f, 0.0f, 1.0f, 1.0f, 1, 0x888888, c, r, input->is_higlighted[r][c]);
            if (input->digit[r][c] > 0)
                cellbox->draw_char('0' + input->digit[r][c], 0.4f, 0.3f);
            delete cellbox;
        }
    }

    // 3x3 boxes
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            sudokubox.draw_box((1.0 / 3) * r, (1.0 / 3) * c, cell_size * 3, cell_size * 3, 2, 0x555555);
        }
    }
    // outer box
    sudokubox.draw_box(0, 0, 1.0f, 1.0f, 6, 0x000000);
}