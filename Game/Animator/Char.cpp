#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Char.h"

Char::Char(std::string fileName, sf::RenderWindow* window) 
:   spriteSheet(fileName), 
    elapsedTime(sf::seconds(0)), 
    position(std::make_pair(0, 0)),
    currentSpriteIndex(0), 
    state(CharState::IDLE),
    window(window){ 

    idleSprites = spriteSheet.makeSprites("IDLE", std::make_pair(0, 15), 50, 85, 4);
    walkSprites = spriteSheet.makeSprites("WALK", std::make_pair(202, 15), 49, 85, 5);
    currentSpriteSheet = &idleSprites;
}
void debug(std::string s);

sf::Sprite Char::getCurrentSprite(){
    return *(currentSpriteSheet->at(currentSpriteIndex));
}

void Char::getPosition(){
    std::cout << position.first << "," << position.second << "\n" << std::flush;
}

void Char::draw(){
    window->draw(getCurrentSprite());
}

void Char::nextFrame(){
    currentSpriteIndex = currentSpriteIndex < (currentSpriteSheet->size() - 1) ? 
          (currentSpriteIndex + 1) : 0;
}
void Char::update(sf::Time elapsedTime, bool isOpponent){
    this->elapsedTime += elapsedTime;
    if(this->elapsedTime > sf::seconds(0.005f)){
        nextFrame();
        this->elapsedTime = sf::seconds(0);
    }
    int scale = 500;
    if(isOpponent){
        scale *= 20;
    }
    switch(state){
        case CharState::WALKLEFT:
            position.first -= elapsedTime.asSeconds() * scale;
            break;
        case CharState::WALKRIGHT: 
            position.first += elapsedTime.asSeconds() * scale;
            break;
        default: 
            break;
    }
    //Update sprite position to draw
    currentSpriteSheet->at(currentSpriteIndex)->setPosition(sf::Vector2f(position.first, position.second));
}
void Char::updateState(CharState::STATE st){
    if(this->state != st){
        this->state = st;
        currentSpriteIndex = 0;
        switch(st){
            case CharState::IDLE:
                currentSpriteSheet = &idleSprites;
                break;
            case CharState::WALKLEFT:
                currentSpriteSheet = &walkSprites;
                break;
            case CharState::WALKRIGHT: 
                currentSpriteSheet = &walkSprites;
                break;
            default: 
                break;
        }
    }
}

std::vector<sf::Sprite*>::iterator it;



