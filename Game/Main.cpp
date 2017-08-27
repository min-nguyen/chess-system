#include <stdio.h>
#include <iostream>
#include "Char.h"
#include <SDL2/SDL.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Client.h"
#include "Server.h"

#undef main

void prnt(std::string string){
    std::cout << string << std::flush;
}
void createClient(Client client){
    client.run();
}
void createServer(Server server){
    server.run();
}

int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::RenderTexture rendertexture;
    sf::CircleShape shape(100.f);
    

    //std::system("../Client/Client");
    //sf::Thread thread(createServer);
    //thread.launch();
    Server server;
    sf::Thread threadA(createServer, server);
    threadA.launch();
    
    // sf::Thread thread(client.run());
    // Char c("SF.gif");   
    sf::Clock clock;
    
    while (window.isOpen())
    {
        sf::Event event;
        // while (window.pollEvent(event))
        // {   
        //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        //         c.input(CharState::WALKLEFT);
        //     }
        //     else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        //         c.input(CharState::WALKRIGHT);
        //     }
        //     else {
        //         c.input(CharState::IDLE);
        //     }

            
        //     if(event.type == sf::Event::Closed)
        //         window.close();
            
        // }
        
        // c.update(clock.getElapsedTime());
        
        // window.draw(shape);
        // window.draw(c.getCurrentSprite() );
        window.display();
        window.clear();
        clock.restart();
    }

    return 0;
}
