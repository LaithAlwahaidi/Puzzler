#pragma once
#include "Sudoku.h"

class NoDigitFoundException : public std::exception
{
    const char* what() const throw()
    {
        return "No valid digit found";
    }
};

class Solver
{
private:
    Sudoku& puzzle;
    Sudoku::Cell find_one_possible();

public:
    Solver(Sudoku& new_puzzle);
    void solve();
    void fill_digit(Sudoku::Cell cell);
    // void fill_digit_threaded(int row, int col, int digit, thread &th);
    void update_possible(Sudoku::Cell cell);
};