#include "cell.h"
#include "globalConsts.h"
#include <iostream>

Cell::Cell() {

}

void Cell::display(sf::RenderWindow &window, int i, int j) {
    // create sprite and texture
    sf::Sprite icon;
    sf::Texture texture;

    // load image sprite and set texture
    texture.loadFromFile("Images/Icons32.png");
    icon.setTexture(texture);

    // creates cell shape
    sf::RectangleShape curCell(sf::Vector2f(CELLSIZE - 1, CELLSIZE - 1));

    // sets position of current square based on indices
    curCell.setPosition(static_cast<float>(CELLSIZE * i), static_cast<float>(CELLSIZE * j));

    // sets color of square based on whether the square has been clicked
    curCell.setFillColor(this->isOpened ? sf::Color( 105, 105, 105) : sf::Color(169, 169, 169));

    // draws square
    window.draw(curCell);

    /*
    if (isMine) {
        icon.setPosition(static_cast<float>(CELLSIZE * i), static_cast<float>(CELLSIZE * j));
        icon.setTextureRect(sf::IntRect(CELLSIZE, 0, CELLSIZE, CELLSIZE));
        window.draw(icon);
    }
     */

    // displays number of bombs in a 1 square range if square has been clicked
    // to do
    if (isOpened && nearbyMines > 0) {
        icon.setPosition(static_cast<float>(CELLSIZE * i), static_cast<float>(CELLSIZE * j));
        icon.setTextureRect(sf::IntRect(CELLSIZE * nearbyMines, 0, CELLSIZE, CELLSIZE));
        window.draw(icon);
    }

    // display flag icon if flagged
    if (isFlagged) {
        // setting flags position
        icon.setPosition(static_cast<float>(CELLSIZE * i), static_cast<float>(CELLSIZE * j));

        // using only a section of Icons.png: flag is in the first square
        icon.setTextureRect(sf::IntRect(0, 0, CELLSIZE, CELLSIZE));
        window.draw(icon);
    }

}

void Cell::setMine() {
    this->isMine = !this->isMine;
}

bool Cell::getMine() {
    return this->isMine;
}

// to do
void Cell::open(Cell cells[ROWS][COLS], int x, int y) {
    std::cout << "Test: current row/col: " << x << ", " << y << std::endl;
    if (x < 0 || y < 0 || x >= ROWS || y >= COLS || cells[x][y].isOpened || cells[x][y].isMine) return;
    cells[x][y].isOpened = true;
    getNearby(cells, x, y);
    //std::cout << nearbyMines;

    if (cells[x][y].nearbyMines == 0) {
        open(cells, x - 1, y);
        open(cells, x + 1, y);
        open(cells, x, y - 1);
        open(cells, x, y + 1);
    }
}

void Cell::getNearby(Cell cells[ROWS][COLS], int x, int y) {
    for (int i = x - 1; i < x + 2; ++i) {
        for (int j = y - 1; j < y + 2; ++j) {
            if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
                if (cells[i][j].getMine()) cells[x][y].nearbyMines++;
            }
        }
    }
}

bool Cell::getOpen() {
    return this->isOpened;
}

bool Cell::getFlag() {
    return this->isFlagged;
}

void Cell::setFlag() {
    this->isFlagged = !this->isFlagged;
}

void Cell::reset() {
    this->isFlagged = false;
    this->isOpened = false;
    this->isMine = false;
}