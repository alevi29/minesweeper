#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

#include <SFML/Graphics.hpp>

class Cell {
    bool isMine = false;
    bool isFlagged = false;
    bool isOpened = false;
    int nearbyMines;

    public:

    Cell();

    void displayNearby();

    void display(sf::RenderWindow &window, int i, int j);

    void setMine();

    bool getMine();

    void open();

    bool getOpen();

    void setFlag();

    bool getFlag();

    void reset();
};

#endif //MINESWEEPER_CELL_H
