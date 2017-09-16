#ifndef CHESS_H
#define CHESS_H

#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"

namespace ChessTeam {
    enum Team {
        Blue, 
        Red,
        Empty
    };
};

class Chess{
public: 
    Chess(ChessTeam::Team team, std::string fileName);
    void remove();
    void add();
    virtual void move();
    std::vector<std::pair<int, int> > validMoves;
    ChessTeam::Team team;
protected:
    sf::Sprite* icon = nullptr;
    SpriteSheet spriteMaker;
private:
}; 

 
#endif 