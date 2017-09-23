#ifndef ANIMATION_H
#define ANIMATION_H


#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"

enum class AnimationState {
        IDLE,
        WALKRIGHT,
        WALKLEFT
};

class Animation {
public:
    Animation(std::string t_fileName, sf::RenderWindow* t_window);
    void debug(std::string s);
    sf::Sprite getCurrentSprite();
    void update(sf::Time elapsedTime, bool isOpponent);
    void updateState(AnimationState st);
    void getPosition();
    void draw();
    std::pair<float, float> position;
protected:
    SpriteSheet spriteSheet;
    sf::RenderWindow* window;
    std::vector<sf::Sprite> idleSprites;
    std::vector<sf::Sprite> walkSprites;
    std::vector<sf::Sprite>::iterator it;
    void nextFrame();
    int currentSpriteIndex;
    std::vector<sf::Sprite>* currentSpriteSheet;
    AnimationState state;
    sf::Time elapsedTime;
private:
    
};

#endif