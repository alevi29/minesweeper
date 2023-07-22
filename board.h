#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include <vector>
#include "globalConsts.h"
#include <SFML/Graphics.hpp>
#include "cell.h"
#include <random>

class Board {
    bool firstClick;
    bool gameOver;
    bool gameWon;

    Cell cells[ROWS][COLS] = {};

    public:
    Board();

    void initialize();

    void draw(sf::RenderWindow &window);

    void openCell(int x, int y);

    void flagCell(int x, int y);

    void restart();

    bool isGameOver();

    void setGameOver();

    bool getGameWon();
};

#endif //MINESWEEPER_BOARD_H
