
#include "Animation.h"

Animation::Animation(std::string t_fileName, sf::RenderWindow* t_window) 
:   spriteSheet(t_fileName), 
    elapsedTime(sf::seconds(0)), 
    position(std::make_pair(0, 0)),
    currentSpriteIndex(0), 
    state(AnimationState::IDLE),
    window(t_window){ 

    idleSprites = spriteSheet.makeSprites("IDLE", std::make_pair(0, 15), 50, 85, 4);
    walkSprites = spriteSheet.makeSprites("WALK", std::make_pair(202, 15), 49, 85, 5);
    currentSpriteSheet = &idleSprites;
}
void debug(std::string s);

sf::Sprite Animation::getCurrentSprite(){
    return (currentSpriteSheet->at(currentSpriteIndex));
}

void Animation::getPosition(){
    std::cout << position.first << "," << position.second << "\n" << std::flush;
}

void Animation::draw(){
    window->draw(getCurrentSprite());
}

void Animation::nextFrame(){
    currentSpriteIndex = currentSpriteIndex < (currentSpriteSheet->size() - 1) ? 
          (currentSpriteIndex + 1) : 0;
}
void Animation::update(sf::Time elapsedTime, bool isOpponent){
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
        case AnimationState::WALKLEFT:
            position.first -= elapsedTime.asSeconds() * scale;
            break;
        case AnimationState::WALKRIGHT: 
            position.first += elapsedTime.asSeconds() * scale;
            break;
        default: 
            break;
    }
    //Update sprite position to draw
    currentSpriteSheet->at(currentSpriteIndex).setPosition(sf::Vector2f(position.first, position.second));
}
void Animation::updateState(AnimationState st){
    if(this->state != st){
        this->state = st;
        currentSpriteIndex = 0;
        switch(st){
            case AnimationState::IDLE:
                currentSpriteSheet = &idleSprites;
                break;
            case AnimationState::WALKLEFT:
                currentSpriteSheet = &walkSprites;
                break;
            case AnimationState::WALKRIGHT: 
                currentSpriteSheet = &walkSprites;
                break;
            default: 
                break;
        }
    }
}




