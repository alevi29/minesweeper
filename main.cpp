#include "globalConsts.h"
#include "cell.h"
#include "board.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

int main()
{
    // renders window with dimensions
    sf::RenderWindow window(sf::VideoMode(CELLSIZE * COLS, CELLSIZE * ROWS), "Minesweeper");

    // creating the event
    sf::Event event;

    // creating the board
    Board theBoard;

    while (window.isOpen())
    {

        int mouseX = static_cast <int>(floor(static_cast <float>(sf::Mouse::getPosition(window).x) / static_cast <float> (CELLSIZE)));
        int mouseY = static_cast <int>(floor(static_cast <float>(sf::Mouse::getPosition(window).y) / static_cast <float> (CELLSIZE)));

        if (mouseX < 0) mouseX = 0;
        else if (mouseX > COLS - 1) mouseX = COLS - 1;

        if (mouseY < 0) mouseY = 0;
        else if (mouseY > ROWS - 1) mouseY = ROWS - 1;

        //std::cout << "Current mouse position: (" << mouseX << ", " << mouseY << ")\n";

        // loop that checks for user input
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case (sf::Event::Closed):
                    window.close();
                    break;

                case (sf::Event::MouseButtonPressed):

                    if (event.mouseButton.button == sf::Mouse::Left) theBoard.openCell(mouseX, mouseY);

                    else if (event.mouseButton.button == sf::Mouse::Right) theBoard.flagCell(mouseX, mouseY);
                    break;

                case (sf::Event::KeyReleased):
                    if (event.key.code == sf::Keyboard::R) theBoard.restart();
                    break;

            }
        }
        if (theBoard.isGameOver()) {
            std::cout << "Game over!";
            theBoard.restart();
        }

        window.clear();

        theBoard.draw(window);

        window.display();
    }
}