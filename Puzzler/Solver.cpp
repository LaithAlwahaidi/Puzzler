#include "Solver.h"
#include <algorithm>
#include <thread>
#include <future>
#include <assert.h>
#include <iostream>

using namespace std;

Solver::Solver(Sudoku& new_puzzle)
    : puzzle(new_puzzle)
{
    puzzle.fill_possible();
}

Sudoku::Cell Solver::find_one_possible()
{
    for (auto& i : puzzle.empty_cells)
    {
        // cout << i.row << i.col << i.digit;
        if (puzzle.grid[i->row][i->col].possible.size() == 1)
        {
            Sudoku::Cell found_digit;
            found_digit.row = i->row;
            found_digit.col = i->col;
            found_digit.possible = i->possible;
            found_digit.digit = i->possible.front();
            found_digit.previous = i;

            return found_digit;
        }
    }
    throw NoDigitFoundException();
}

void Solver::solve()
{
    while (puzzle.empty_cells.size() > 0)
    {
        try
        {
            Sudoku::Cell found_digit = find_one_possible();
            fill_digit(found_digit);
        }
        catch (NoDigitFoundException & e)
        {
            cout << "no digits found\n";
            break;
        }
    }
}

void Solver::fill_digit(Sudoku::Cell cell)
{
    puzzle.grid[cell.row][cell.col] = cell;
    puzzle.empty_cells.erase(remove(puzzle.empty_cells.begin(), puzzle.empty_cells.end(), cell.previous), puzzle.empty_cells.end());
    update_possible(cell);
    // void (SolverA::*fpd)(int, int, int) = &update_possible;
    // future<void> update_async = async(fpd, this, row, col, digit);
    // update_thread.join();
}

void Solver::update_possible(Sudoku::Cell cell)
{
    for (int i = 0; i < 9; i++)
    {
        vector<int>* cur = &puzzle.grid[cell.row][i].possible;
        cur->erase(remove(cur->begin(), cur->end(), cell.digit), cur->end());

        cur = &puzzle.grid[i][cell.col].possible;
        cur->erase(remove(cur->begin(), cur->end(), cell.digit), cur->end());
    }
    int r = (cell.row / 3) * 3;
    int c = (cell.col / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            vector<int>* cur = &puzzle.grid[r + i][c + j].possible;
            cur->erase(remove(cur->begin(), cur->end(), cell.digit), cur->end());
        }
    }
}
