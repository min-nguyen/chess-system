#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Client.h"
#include <functional>
#include <thread>
#include "Grid.h"
// #undef main

void createClient(Client& client){
    client.run();
    std::cout << "running " << std::flush;
}


int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::RenderTexture renderTexture;
    sf::Clock clock;
    sf::Time elapsedTime = clock.restart();

    Grid grid(&window);

    while (window.isOpen())
    {   
            clock.restart();
            sf::Event event;
            while (window.pollEvent(event)){
                //Process our character actions
                if(event.type == sf::Event::KeyPressed){

                }
                if(event.type == sf::Event::Closed)
                    window.close();
            }
            // //Update and draw both characters
            // sf::Time now = clock.getElapsedTime();
            grid.drawGrid();
            window.display();
            window.clear();
            
        
    }

    return 0;
}