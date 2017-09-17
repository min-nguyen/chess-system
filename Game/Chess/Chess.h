#ifndef CHESS_H
#define CHESS_H

#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"


enum class ChessTeam {
        Blue, 
        Red,
        Empty
};

class Chess{
public: 
    Chess(const ChessTeam team, std::string fileName, sf::RenderWindow* window);
    //Generic functions
    void move(const int x, const int y);
    //Abstract functions
    virtual void remove() = 0;
    virtual void add() = 0;
    virtual void draw() = 0;
    //Chess piece properties
    std::vector<std::pair<int, int> > validMoves;
    std::pair<int, int> position;
    const ChessTeam team;
protected:
    sf::Sprite icon;
    SpriteSheet spriteMaker;
    sf::RenderWindow* window;
private:
}; 

 
#endif 