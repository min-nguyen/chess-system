#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"

namespace CharState {
    enum STATE {
        IDLE,
        WALKRIGHT,
        WALKLEFT
    };
}

class Char {
public:
    Char(std::string fileName, sf::RenderWindow* window);
    void debug(std::string s);
    sf::Sprite getCurrentSprite();
    void update(sf::Time elapsedTime);
    void updateState(CharState::STATE st);
    void draw();
    std::pair<float, float> position;
protected:
    SpriteSheet spriteSheet;
    sf::RenderWindow* window;
    std::vector<sf::Sprite*> idleSprites;
    std::vector<sf::Sprite*> walkSprites;
    std::vector<sf::Sprite*>::iterator it;
    void nextFrame();
    int currentSpriteIndex;
    std::vector<sf::Sprite*>* currentSpriteSheet;
    CharState::STATE state;
    sf::Time elapsedTime;
private:
    
};