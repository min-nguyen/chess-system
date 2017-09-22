#ifndef HOSTROOM_H
#define HOSTROOM_H

#include <stdio.h>
#include <stdlib.h>
#include "SpriteSheet.h"
#include "Client.h"
#include "Grid.h"
#include <utility>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

class HostRoom{
public: 
    HostRoom(sf::RenderWindow* t_window, Client& t_client);
    void draw();
    void update();
    void processInput(sf::Vector2i position);
protected:
    SpriteSheet spriteMaker;
    sf::RenderWindow* window;
    sf::Font font;
    std::vector<sf::Text> widgets;
    sf::Sprite hostRoomButton;
private:
    Grid grid;
    sf::Text title;
    Client& client;
}; 

class Tab {

};
 
#endif 