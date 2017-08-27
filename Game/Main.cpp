#include <stdio.h>
#include <iostream>
#include "Char.h"
#include <SDL2/SDL.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Client.h"
#include "Server.h"
#include <functional>
#undef main

void prnt(std::string string){
    std::cout << string << std::flush;
}
void createClient(Client& client){
    std::cout << &client << "\n" << std::flush;
    client.run();
}
void createServer(Server& server){
    server.run();
}

int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::RenderTexture rendertexture;
    sf::CircleShape shape(100.f);
    
    Client client; 
    sf::Thread threadA(&createClient, std::ref(client));
    threadA.launch();
    std::cout << &client << "\n" << std::flush;
    sf::Clock clock;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                client.outBuffer('L');
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                client.outBuffer('R');
            }
            if(event.type == sf::Event::Closed)
                window.close();
            
        }
        
        window.display();
        window.clear();
        clock.restart();
    }

    return 0;
}
