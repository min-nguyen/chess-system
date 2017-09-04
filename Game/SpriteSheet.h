#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class SpriteSheet{
public:
    
    SpriteSheet(std::string fileName);
    
    std::vector<sf::Sprite*> makeSprites(std::string name, 
                                        std::pair<int, int> coordinates, 
                                        int width, 
                                        int height, 
                                        int numSprites);
    

    sf::Texture texture;
    sf::Sprite spriteSheet;
};

#endif