#include "Snake.h"

Snake::Snake(sf::RenderWindow* window) 
:   
    spriteSheet("./sqr.png"),
    elapsedTime(sf::seconds(0)), 
    position(std::make_pair(0, 0)),
    currentSpriteIndex(0), 
    state(State::R),
    window(window){ 
    
    currentSprites = spriteSheet.makeSprites(" ", std::make_pair(0, 0), 40, 40, 1);
        
}

void Snake::getPosition(){
    std::cout << position.first << "," << position.second << "\n" << std::flush;
}

void Snake::draw(){
    
    window->draw(*(currentSprites.at(0))) ;
}

void Snake::run(sf::Time elapsedTime){
    sf::Event event;
    while (window->pollEvent(event)){
        //Process our character actions
        if(event.type == sf::Event::KeyPressed){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                updateState(State::L);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                updateState(State::R);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                updateState(State::U);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                updateState(State::D);
            }
        }
    }
    //Update and draw both characters
    getPosition();
    update(elapsedTime); 
    draw();
}

void Snake::update(sf::Time time){
    int scale = 500;

    switch(state){
        case State::L:
            position.first -= (time.asSeconds() * scale);
            break;
        case State::R: 
            position.first += (time.asSeconds() * scale);
            break; 
        case State::U: 
            position.second -= time.asSeconds() * scale;
            break; 
        case State::D: 
            position.second += time.asSeconds() * scale;
            break; 
        default: 
            break;
    }
    currentSprites.at(currentSpriteIndex)->setPosition(sf::Vector2f(position.first, position.second));
}

void Snake::updateState(State::SnakeState st){
    if(this->state != st){
        this->state = st;
        currentSpriteIndex = 0;
        switch(st){
            case State::L:
                state = State::L;
                break;
            case State::R:
                state = State::R;
                break;
            case State::U:
                state = State::U;
                break;
            case State::D:
                state = State::D;
                break;
            default: 
                break;
        }
    }
}



