#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

#include <SFML/Graphics.hpp>
#include "globalConsts.h"

class Cell {
    bool isMine = false;
    bool isFlagged = false;
    bool isOpened = false;
    int nearbyMines = 0;

    public:

    Cell();

    void getNearby(Cell cells[ROWS][COLS], int x, int y);

    void display(sf::RenderWindow &window, int i, int j);

    void setMine();

    bool getMine();

    void open(Cell cells[ROWS][COLS], int x, int y);

    bool getOpen();

    void setFlag();

    bool getFlag();

    void reset();
};

#endif //MINESWEEPER_CELL_H
