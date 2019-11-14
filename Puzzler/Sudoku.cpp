#include "Sudoku.h"
#include <algorithm>
#include <iostream>

using namespace std;

Sudoku::Sudoku(array<array<int, 9>, 9> entries)
{
    for (int row = 0; row < (sizeof(entries) / sizeof(entries[0])); row++)
    {
        for (int col = 0; col < (sizeof(entries[row]) / sizeof(entries[row][0])); col++)
        {
            Cell cell = {};
            cell.row = row;
            cell.col = col;
            cell.digit = entries[row][col];
            if (!cell.digit)
            {
                cell.possible = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
                empty_cells.push_back(&grid[row][col]);
            }
            else
                cell.possible = {};

            cell.previous = nullptr;
            grid[row][col] = cell;
        }
    }
}

string Sudoku::to_string()
{
    string stringgrid = "";

    for (int row = 0; row < 9; row++)
    {
        string stringpossible = "";
        for (int col = 0; col < 9; col++)
        {
            stringgrid.append(std::to_string(grid[row][col].digit));
            stringgrid.append(" ");

            stringpossible.append("{ ");
            for (int k = 0; k < grid[row][col].possible.size(); k++)
            {
                stringpossible.append(std::to_string(grid[row][col].possible[k]));
                stringpossible.append(", ");
            }
            stringpossible.append(" }");
        }
        stringgrid.append("         ");
        stringgrid.append(stringpossible);
        stringgrid.append("\n");
    }

    return stringgrid;
}

bool Sudoku::is_legal_digit(int row, int col, int digit)
{
    for (int i = 0; i < 9; i++)
    {
        if (grid[row][i].digit == digit || grid[i][col].digit == digit)
            return false;
    }
    int r = (row / 3) * 3;
    int c = (col / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[r + i][c + j].digit == digit)
                return false;
        }
    }
    return true;
}

void Sudoku::fill_possible(Cell* cell)
{
    // Cell new_cell = cell;

    for (int i = 0; i < 9; i++)
    {
        cell->possible.erase(remove(cell->possible.begin(), cell->possible.end(), grid[cell->row][i].digit), cell->possible.end());
        cell->possible.erase(remove(cell->possible.begin(), cell->possible.end(), grid[i][cell->col].digit), cell->possible.end());
    }
    int r = (cell->row / 3) * 3;
    int c = (cell->col / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cell->possible.erase(remove(cell->possible.begin(), cell->possible.end(), grid[r + i][c + j].digit), cell->possible.end());
        }
    }
}

void Sudoku::fill_possible()
{
    for (auto& i : empty_cells)
    {
        fill_possible(i);
    }
}