#include <stdio.h>
#include <stdlib.h>
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
    std::cout << "running " << std::flush;
}

void createServer(Server& server){
    server.run();
}

void updateOpponent(Client& client, Char& c2, sf::Clock& clock){
    while(true){
        
    }
}

int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode(800, 400), "SFML works!");
    sf::RenderTexture renderTexture;
    sf::Clock clock;
    sf::Time elapsedTime = clock.restart();
    Char c("./SF.gif", &window);
    Char c2("./SF.gif", &window);

    Client client; 
    sf::Thread runClient(&createClient, std::ref(client));
    runClient.launch(); 
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::KeyPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    c.updateState(CharState::WALKLEFT);
                    client.outBuffer('L');
                    
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    c.updateState(CharState::WALKRIGHT);
                    client.outBuffer('R');
                }
            }
            else {
                c.updateState(CharState::IDLE);
            }
            char ch = client.inBuffer();
            if (ch == 'L'){
                printf("l");
                c2.updateState(CharState::WALKLEFT);
            }
            else if(ch == 'R'){
                printf("r");
                c2.updateState(CharState::WALKRIGHT);
            }
            else {
                printf("idle");
                c2.updateState(CharState::IDLE);
            }

            if(event.type == sf::Event::Closed)
                window.close();
        }

        c2.update(clock.getElapsedTime());
        c2.draw();
        c.update(clock.getElapsedTime());
        c.draw();
        window.display();
        window.clear();
        clock.restart();
    }

    return 0;
}
