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
#include "Chess.h"
#include "HostRoom.h"

void createClient(Client& client){
    client.run();
    std::cout << "running " << std::flush;
}



int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::RenderTexture renderTexture;
    sf::Clock clock;
    sf::Time elapsedTime = clock.restart();
    
    // Client client; 
    // sf::Thread runClient(&createClient, std::ref(client));
    // runClient.launch(); 

    HostRoom host(&window);

    while (window.isOpen())
    {   
            clock.restart();
            sf::Event event;
            while (window.pollEvent(event)){
                if(event.type == sf::Event::Closed)
                    window.close();
            }
            host.draw();

            window.display();
            window.clear();
    }

    return 0;
}