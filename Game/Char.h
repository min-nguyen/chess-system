#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpriteSheet.cpp"

namespace CharState {
    enum STATE {
        IDLE,
        WALKRIGHT,
        WALKLEFT
    };
}

class Char {
public:
    Char(std::string fileName);
    void debug(std::string s);
    sf::Sprite getCurrentSprite();
    void update(sf::Time elapsedTime);
    void input(CharState::STATE st);
    std::pair<float, float> position;
protected:
    SpriteSheet spriteSheet;
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