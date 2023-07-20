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
            std::cout << "Mine at (" << randX << ", " << randY << ")\n";
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
            //if (cells[i][j].getMine()) std::cout << "Mine at (" << i << ", " << j << ")\n";
        }
    }
}

void Board::openCell(int x, int y) {
    if (!cells[x][y].getOpen()) {
        cells[x][y].open();
        if (cells[x][y].getMine()) {
            if (firstClick) {
                firstClick = false;
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
            else {
                gameOver = true;
            }
        }
    }
}

void Board::flagCell(int x, int y) {
    cells[x][y].setFlag();
}

void Board::restart() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cells[i][j].reset();
        }
    }
    initialize();
    firstClick = true;
    gameOver = false;
}

bool Board::isGameOver() {
    return gameOver;
}