#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"

namespace State {
    enum SnakeState {
        L,
        R,
        U,
        D
    };
}

class Snake {
public:
    Snake(sf::RenderWindow* window);
    State::SnakeState getCurrentState();
    void update(sf::Time elapsedTime);
    void updateState(State::SnakeState st);
    void getPosition();
    void blitCell(int x, int y);
    void draw();
    std::pair<float, float> position;
protected:
    sf::RenderWindow* window;
    int currentSpriteIndex;
    State::SnakeState state;
    sf::Time elapsedTime;
private:
    SpriteSheet spriteSheet;
    std::vector<sf::Sprite*> currentSprites;
};

#endif