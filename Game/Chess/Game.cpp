#include "Game.h"

Game::Game(sf::RenderWindow* t_window): window(t_window){

}

void Game::run(){
    sf::RenderTexture renderTexture;
    sf::Clock clock;
    sf::Time elapsedTime = clock.restart();

    Grid grid(window);
 
    while (window->isOpen()){   
            clock.restart();
            sf::Event event;
            while (window->pollEvent(event)){
                //Process our character actions
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
                    grid.processInput(localPosition);
                }
                if(event.type == sf::Event::Closed)
                    window->close();
            }
            // //Update and draw both characters
            // sf::Time now = clock.getElapsedTime();
            grid.drawGrid();

            window->display();
            window->clear();
    }
}