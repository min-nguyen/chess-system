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
    King(   const ChessTeam t_team, 
            std::string t_fileName, 
            sf::RenderWindow* t_window);
    void move();
    void add();
    void remove();
    void draw();
    static std::string getFileName(){
        return "./chessIcons.png";
    };
    ChessTeam team;
private:

}; 

  
#endif 