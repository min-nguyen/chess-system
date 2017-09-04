#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(std::string fileName){
    if(!texture.loadFromFile(fileName)){
        std::cout << ("Error loading") << std::flush;
    }
    else{
        spriteSheet.setTexture(texture);
    }
} 

std::vector<sf::Sprite*> SpriteSheet::makeSprites(  std::string name, 
                                                    std::pair<int, int> coordinates, 
                                                    int width, 
                                                    int height, 
                                                    int numSprites){
    
    std::vector<sf::Sprite*> sprites;   
    for(int i = 0; i < numSprites; i++){
        sf::Sprite* sprite = new sf::Sprite();
        sprite->setTexture(texture); 
        sprite->setTextureRect(sf::IntRect( coordinates.first + i*width, 
                                            coordinates.second,
                                            width,
                                            height));
        sprites.push_back(sprite);
    }

    return sprites;
}