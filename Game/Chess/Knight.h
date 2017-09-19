#ifndef KNIGHT_H
#define KNIGHT_H

#include <stdio.h>
#include <stdlib.h>
#include "Chess.h"
#include "SpriteSheet.h"
#include <utility>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

class Knight: public Chess{
public: 
    Knight(   const ChessTeam t_team, 
            sf::RenderWindow* t_window,
            std::pair<int, int> t_position);

    void draw() override;
    bool isValid(int x, int y, std::pair<std::shared_ptr<Chess>, ChessTeam> t) override;
    static std::string getFileName(){
        return "./chessIcons.png";
    };
    static std::map<ChessTeam, std::pair<int, int>> getSpriteXY(){
        std::map<ChessTeam, std::pair<int, int>> sprites;
        sprites[ChessTeam::Blue] = std::make_pair(51, 0);
        sprites[ChessTeam::Red] = std::make_pair(51, 46);
        return sprites;
    };
private:

}; 

  
#endif 