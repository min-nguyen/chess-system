#ifndef CHESS_H
#define CHESS_H

#include <stdio.h>
#include <stdlib.h>
#include "SpriteSheet.h"
#include <utility>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

enum class ChessTeam {
        Blue, 
        Red,
        Empty
};

class Chess{
public: 
    Chess(  const ChessTeam team, 
            std::string fileName, 
            std::map<ChessTeam, std::pair<int, int>> t_spriteXY,
            sf::RenderWindow* window, 
            std::pair<int, int> t_position);
    //Move to cell col(x) row(y)    
    void move(int x, int y);
    virtual void draw();
    virtual bool isValid(int x, int y, std::pair<Chess*, ChessTeam> t);
    //Attributes
    std::pair<int, int> position;
    const ChessTeam team;
protected:
    sf::Sprite icon;
    SpriteSheet spriteMaker;
    sf::RenderWindow* window;
private:
}; 

 
#endif 