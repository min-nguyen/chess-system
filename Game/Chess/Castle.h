#ifndef CASTLE_H
#define CASTLE_H

#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Chess.h"

class Castle: public Chess{
public: 
    Castle(   const ChessTeam t_team, 
            std::string t_fileName, 
            sf::RenderWindow* t_window,
            std::pair<int, int> t_position);

    void draw();
    bool isValid(int x, int y);
    static std::string getFileName(){
        return "./chessIcons.png";
    };
    ChessTeam team;
private:

}; 

  
#endif 