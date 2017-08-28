#include <stdio.h>
#include <iostream>
#include "Char.h"
#include <SDL2/SDL.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Client.h"
#include "Server.h"
#include <functional>
#include <thread>
#undef main

void prnt(std::string string){
    std::cout << string << std::flush;
}
void createClient(Client& client){
    client.run();
}
void createServer(Server& server){
    server.run();
}

int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::RenderTexture renderTexture;

    
    // Client client; 
    // sf::Thread threadA(&createClient, std::ref(client));
    // threadA.launch(); 

    sf::Clock clock;
    sf::Time elapsedTime = clock.restart();
    Char c("./SF.gif");

    while (window.isOpen())
    {
        sf::Event event;
    //     // while (window.pollEvent(event))
    //     // {   
    //     //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                
    //     //         client.outBuffer('L');
    //     //     }
    //     //     else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
    //     //         client.outBuffer('R');
    //     //     }
    //     //     if(event.type == sf::Event::Closed)
    //     //         window.close();
    //     // }
        while (window.pollEvent(event))
        {   if(event.type == sf::Event::KeyPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    c.updateState(CharState::WALKLEFT);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    c.updateState(CharState::WALKRIGHT);
                }
            }
            else {
                std::cout << "no pressed" << std::flush;
                c.updateState(CharState::IDLE);
            }
            if(event.type == sf::Event::Closed)
                window.close();
        }

        c.update(clock.getElapsedTime());
        window.draw(c.getCurrentSprite());
        window.display();
        window.clear();
        clock.restart();
    }

    return 0;
}
