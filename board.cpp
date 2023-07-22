#include "board.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "globalConsts.h"
#include <random>

Board::Board() {
    firstClick = true;
    gameOver = false;

    initialize();
}

void Board::initialize() {
    std::random_device randomDevice;
    std::default_random_engine Random(randomDevice());

    std::uniform_int_distribution<int> xDistrib(0, COLS- 1);
    std::uniform_int_distribution<int> yDistrib(0, ROWS - 1);

    for (int i = 0; i < MINECOUNT; ++i) {
        int randX = xDistrib(Random);
        int randY = yDistrib(Random);

        if (!cells[randX][randY].getMine()) {
            cells[randX][randY].setMine();
        }
        else {
            --i;
        }
    }

}

void Board::draw(sf::RenderWindow &window) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cells[i][j].display(window, i, j);
        }
    }
}

void Board::openCell(int x, int y) {
    if (!cells[x][y].getOpen()) {
        // if a mine was clicked
        if (cells[x][y].getMine()) {
            // if first click was a mine, moves the mine away instead of causing game over
            if (firstClick) {
                cells[x][y].setMine();

                int i = 0, j = 0;
                while (i < ROWS && j < COLS && cells[i][j].getMine()) {
                    if (j < COLS - 1) {
                        ++j;
                    }
                    else {
                        j = 0;
                        ++i;
                    }
                }
                cells[i][j].setMine();
            }
                // otherwise, game over
            else {
                gameOver = true;
            }
        }

        cells[x][y].open(cells, x, y);

        if (cells[x][y].getFlag()) cells[x][y].setFlag();

        firstClick = false;
    }
}

void Board::flagCell(int x, int y) {
    if (!cells[x][y].getOpen()) cells[x][y].setFlag();
}

void Board::restart() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cells[i][j].reset();
        }
    }
    initialize();
    firstClick = true;
}

bool Board::isGameOver() {
    return gameOver;
}

void Board::setGameOver() {
    this->gameOver = !this->gameOver;
}