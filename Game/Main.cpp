#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Snake.h"
#include <SDL2/SDL.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Client.h"
#include <functional>
#include <thread>
// #undef main

void createClient(Client& client){
    client.run();
    std::cout << "running " << std::flush;
}

void updateOpponent(Client& client, Snake& c2){
    while(true){
        char ch = client.inBuffer();
        if (ch == 'L'){
            c2.updateState(State::L);
            std::cout << "l" << std::flush;
        }
        else if(ch == 'R'){
            c2.updateState(State::R);
            std::cout << "r" << std::flush;
        }
        else if(ch == 'U'){
            c2.updateState(State::U);
            std::cout << "u" << std::flush;
        }
        else if(ch == 'D'){
            c2.updateState(State::D);
            std::cout << "d" << std::flush;
        }
    }
}

int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode(800, 400), "SFML works!");
    sf::RenderTexture renderTexture;
    sf::Clock clock;
    sf::Time elapsedTime = clock.restart();

    Client client; 
    sf::Thread runClient(&createClient, std::ref(client));
    runClient.launch(); 

    Snake snake(&window);
    Snake snake2(&window);

    sf::Thread updateClient(std::bind(&updateOpponent, std::ref(client), std::ref(snake2)));
    updateClient.launch();


    while (window.isOpen())
    {   
        if(client.isConnected()){
            clock.restart();
            sf::Event event;
            while (window.pollEvent(event)){
                //Process our character actions
                if(event.type == sf::Event::KeyPressed){
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                        snake.updateState(State::L);
                        client.outBuffer('L');
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                        snake.updateState(State::R);
                        client.outBuffer('R');
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        snake.updateState(State::U);
                        client.outBuffer('U');
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                        snake.updateState(State::D);
                        client.outBuffer('D');
                    }
                }
                if(event.type == sf::Event::Closed)
                    window.close();
            }
            //Update and draw both characters
            sf::Time now = clock.getElapsedTime();
            snake.update(now); 
            snake2.update(now); 
            snake2.getPosition();
            snake.draw();
            snake2.draw();
            window.display();
            window.clear();
            
        }
    }

    return 0;
}
