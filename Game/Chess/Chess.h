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
    Chess(  const ChessTeam team, 
            std::string fileName, 
            sf::RenderWindow* window, 
            std::pair<int, int> t_position);
    //Generic functions
    void move(const int x, const int y);
    
    //Abstract functions
    virtual void draw() = 0;
    virtual bool isValid(int x, int y) = 0;
    //Chess piece properties
    std::pair<int, int> position;
    const ChessTeam team;
protected:
    sf::Sprite icon;
    SpriteSheet spriteMaker;
    sf::RenderWindow* window;
private:
}; 

 
#endif 