#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Char.h"
#include <SDL2/SDL.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Client.h"
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
    std::cout << "here" << std::flush;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            //Process our character actions
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
            if(event.type == sf::Event::Closed)
                window.close();
        }
        //Process opponent actions
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
            c2.updateState(CharState::IDLE);
        }

        //Update and draw both characters
        c2.update(clock.getElapsedTime(), true);
        c.update(clock.getElapsedTime(), false); 
        c.getPosition();
        c2.draw();
        c.draw();
        window.display();
        window.clear();
        clock.restart();
    }

    return 0;
}
