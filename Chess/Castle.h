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
            sf::RenderWindow* t_window,
            std::pair<int, int> t_position);

    void draw() override;
    bool isValid(int x, int y, std::pair<Chess*, ChessTeam> t) override;
    static std::string getFileName(){
        return "./chessIcons.png";
    };
    static std::map<ChessTeam, std::pair<int, int>> getSpriteXY(){
        std::map<ChessTeam, std::pair<int, int>> sprites;
        sprites[ChessTeam::Blue] = std::make_pair(165, 0);
        sprites[ChessTeam::Red] = std::make_pair(165, 46);
        return sprites;
    };
private:

}; 

  
#endif 