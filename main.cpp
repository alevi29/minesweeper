#include "globalConsts.h"
#include "cell.h"
#include "board.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

int main()
{
    bool activeGame = true;

    // renders window with dimensions
    sf::RenderWindow window(sf::VideoMode(CELLSIZE * COLS, CELLSIZE * ROWS + TEXTSIZE), "Minesweeper");

    // creating the event
    sf::Event event;

    // creating the board
    Board theBoard;

    sf::Font font;
    font.loadFromFile("Images/COMIC.TTF");

    sf::Text text;
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    text.setPosition(0, CELLSIZE * ROWS);
    text.setCharacterSize(TEXTSIZE);

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
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (!theBoard.isGameOver()) {
                switch (event.type) {
                    case (sf::Event::MouseButtonPressed):

                        if (event.mouseButton.button == sf::Mouse::Left) theBoard.openCell(mouseX, mouseY);

                        else if (event.mouseButton.button == sf::Mouse::Right) theBoard.flagCell(mouseX, mouseY);
                        break;

                    case (sf::Event::KeyReleased):
                        if (event.key.code == sf::Keyboard::R) theBoard.restart();
                        break;

                }
            }

            else {
                activeGame = false;
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        theBoard.setGameOver();
                        activeGame = true;
                    }
                }
            }
        }



        window.clear();

        theBoard.draw(window);

        if (theBoard.isGameOver()) {
            text.setString("Game over! Press Enter to restart");
            window.draw(text);
            if (activeGame) theBoard.restart();
        }

        window.display();
    }
}