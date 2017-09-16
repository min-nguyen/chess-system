#ifndef KING_H
#define KING_H

#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Chess.h"

class King: Chess{
public: 
    King(ChessTeam::Team team, std::string fileName);
    void move();
    ChessTeam::Team team;
private:
    sf::Sprite* icon = nullptr;
}; 

  
#endif 