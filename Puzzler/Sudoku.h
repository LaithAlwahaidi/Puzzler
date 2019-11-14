#pragma once
#include <string>
#include <vector>
#include <array>

class Sudoku
{

private:
public:
    struct Cell
    {
        int row, col;
        int digit;
        std::vector<int> possible;

        Cell* previous;
    };

    std::array<std::array<Cell, 9>, 9> grid;

    // std::array<std::array<int, 9>, 9> grid;
    // std::vector<std::vector<std::vector<int>>> possible;
    std::vector<Cell*> empty_cells;

    Sudoku(std::array<std::array<int, 9>, 9> entries);
    // ~Sudoku();
    std::string to_string();
    bool is_legal_digit(int row, int col, int digit);
    void fill_possible();
    void fill_possible(Cell* cell);
};
