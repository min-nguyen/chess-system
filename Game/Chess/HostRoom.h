#ifndef HOSTROOM_H
#define HOSTROOM_H

#include <stdio.h>
#include <stdlib.h>
#include "SpriteSheet.h"
#include <utility>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

class HostRoom{
public: 
    HostRoom(sf::RenderWindow* t_window);
    //Generic functions
    void draw();
    void insertRoom();
    void deleteRoom();
protected:
    // SpriteSheet spriteMaker;
    sf::RenderWindow* window;
    sf::Font font;
    std::vector<sf::Text> tabs;
private:
}; 

class Tab {

};
 
#endif 