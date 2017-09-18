#ifndef KING_H
#define KING_H

#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Chess.h"

class King: public Chess{
public: 
    King(   const ChessTeam t_team, 
            sf::RenderWindow* t_window,
            std::pair<int, int> t_position);

    void draw();
    bool isValid(int x, int y, std::pair<std::shared_ptr<Chess>, ChessTeam>  t);
    static std::string getFileName(){
        return "./chessIcons.png";
    };
    static std::map<ChessTeam, std::pair<int, int>> getSpriteXY(){
        std::map<ChessTeam, std::pair<int, int>> sprites;
        sprites[ChessTeam::Blue] = std::make_pair(0, 0);
        sprites[ChessTeam::Red] = std::make_pair(0, 46);
        return sprites;
    };
    ChessTeam team;
private:
    std::vector<std::pair<int, int> > validMoves;
}; 

  
#endif 